#include "main.h"

// find an active touch with the specified id, or allocate a free one from the list.
CTouch* GetTouch(int32 id) {
	CTouch* inactive = NULL;
    
	for(uint32 i=0; i < MAX_TOUCHES; i++) {
		// if we've found a touch with the specified id, return its memory address.
		if(id == touches[i].id) return &touches[i];
		// if no touches are found with the id, pInActive will end up being set to
		// last touch in g_Touches.
		if(!touches[i].active)
            inactive = &touches[i];
	}
    
	// return last inactive touch and assign its id to the specified id.
	if (inactive) {
		inactive->id = id;
		return inactive;
	}
    
	// no more touches; give up.
	return NULL;
}

bool renderTouches(CTouch touches[]) {
	bool true_so_far = true;

	for(int i = 0; i < MAX_TOUCHES; ++i) {
        if(touches[i].active) {
            if(touches[i].gesture_type == CREATE_UNIT)
                true_so_far &= renderDragUnit(&touches[i]);
            else
                true_so_far &= renderDragWorld(&touches[i]);
		}
	}

	return true_so_far;
}



bool renderUnitCreation(CTouch* touch) {
    if(!touch->unit)
        return false;
    
    CIwFVec2 radii = game->getWorldRadius();
    CIwFVec2 *modelCoords = worldify(touch->x, touch->y, radii.x, game->getRotation());
    
    float dist_sq = SQ(modelCoords->x) + SQ(modelCoords->y);
    if(dist_sq > SQ(radii.y) || dist_sq < SQ(radii.x)){
        free(touch->unit);
        delete modelCoords;
        return false;
    }
    
    touch->unit->setPosition(*modelCoords);
	game->addUnit(touch->unit);
    
    touch->unit = NULL;
    touch->active = false;
    
    delete modelCoords;
    
    return true;
}

bool renderDragUnit(CTouch* touch){
	if (!touch->unit) return false;
	else {
        touch->unit->displayOnScreen(touch->x, touch->y);
		return true;
	}
}

bool renderDragWorld(CTouch* touch) {
    if(touch->start_y != touch->end_y || touch->start_x != touch->end_x){
		float inner_radius = game->getWorldRadius().x;
		CIwFVec2 *start_pos_world = worldify(touch->start_x, touch->start_y, inner_radius, game->getRotation());
		CIwFVec2 *end_pos_world = worldify(touch->end_x, touch->end_y, inner_radius, game->getRotation());

		float angle = angle_diff(start_pos_world, end_pos_world);
		game->rotate(angle);

		touch->start_x = touch->end_x;
		touch->start_y = touch->end_y;
    }
    return true;
}


// assign activity and position info to the touch struct associated with an event
// for a multitouch click.
void MultiTouchButtonCB(s3ePointerTouchEvent* event) {
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch) {
        touch->active = event->m_Pressed != 0;
		touch->x = event->m_x;
		touch->y = event->m_y;

        // if it's the beginning of a touch, then determine what kind of gesture it is and set initial info.
        if (touch->active) {
            touch->start_x = touch->end_x = touch->x;
            touch->start_y = touch->end_y = touch->y;
            if (touch->x > (int32) IwGxGetScreenWidth() - 60) {
                touch->gesture_type = CREATE_UNIT;
                
                int y = touch->y - 110; // Palate offset
                if(y < 0) return;
                
                switch (y / 60) { // 60px is size of icons
                    //case 0: touch->unit = new Thrower(NULL,  game, CIwFVec2(0,0)); break;
                    case 1: touch->unit = new Wrecker(localPlayer,  game, 0, 0); break;
                    case 2: touch->unit = new Muncher(localPlayer,  game, 0, 0); break;
                    case 3: touch->unit = new Shooter(localPlayer,  game, 0, 0); break;
                    case 4: touch->unit = new Spreader(localPlayer, game, 0, 0); break;
                    //case 5: touch->unit = new Invader(NULL,  game, CIwFVec2(0,0)); break;
                    default: break;
                }
                   
            } else {
                touch->gesture_type = DRAG_WORLD;
            }
        // if it's the end of a touch, check what kind of gesture it and render.
        } else {
            if (touch->gesture_type == CREATE_UNIT) {
                renderUnitCreation(touch);
            }
        }
	}
}

// assign position info to the touch struct associated with an event for
// multitouch motion.
void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event) {
    if(event->m_x < 0) return;
    
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch) {
		touch->x = event->m_x;
		touch->y = event->m_y;
        
        if (touch->gesture_type == DRAG_WORLD) {
            // sent new start to the old end, and the new end to the new pos
			touch->start_x = touch->end_x;
            touch->start_y = touch->end_y;
			touch->end_x = touch->x;
            touch->end_y = touch->y;
        }   
	}
}

void SingleTouchButtonCB(s3ePointerEvent* event){
    s3ePointerTouchEvent *e2 = (s3ePointerTouchEvent*) malloc(sizeof(s3ePointerTouchEvent));
    e2->m_x = event->m_x;
    e2->m_y = event->m_y;
    e2->m_Pressed = event->m_Pressed;
    e2->m_TouchID = 0;
    MultiTouchButtonCB(e2);
    free(e2);   
}

void SingleTouchMotionCB(s3ePointerMotionEvent* event){
    s3ePointerTouchMotionEvent *e2 = (s3ePointerTouchMotionEvent*) malloc(sizeof(s3ePointerTouchMotionEvent));
    e2->m_x = event->m_x;
    e2->m_y = event->m_y;
    e2->m_TouchID = 0;
    MultiTouchMotionCB(e2);
    free(e2);
}

void doMain() {
    
    s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);
    s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);

	s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);
    s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);

    
    IwGetResManager()->LoadGroup("resource_groups/palate.group");
    CIwResGroup* palateGroup = IwGetResManager()->GetGroupNamed("Palate");
    CIwMaterial* mat = new CIwMaterial();
    mat->SetTexture((CIwTexture*)palateGroup->GetResNamed("palate", IW_GX_RESTYPE_TEXTURE));
    mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
    mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
        
	static CIwSVec2 xy(260, 0);
	static CIwSVec2 wh(60, 480);
	static CIwSVec2 uv(0, 0);
	static CIwSVec2 duv(IW_GEOM_ONE, IW_GEOM_ONE);
    
    CIwColour col = {255, 180, 180, 255};
	localPlayer = new Player(col);
    game = new Game(localPlayer);

	IwGxLightingOff();

	while (1) {
        int64 start = s3eTimerGetMs();
	
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		
		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
				|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
				|| (s3eDeviceCheckQuitRequest())) {
			
		    break;
		}
        
        IwGxSetColClear(255, 255, 255, 255);
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
        
        IwGxSetMaterial(mat);
        IwGxSetScreenSpaceSlot(-1);
        IwGxDrawRectScreenSpace(&xy, &wh, &uv, &duv);
        
        game->tick();
        
		renderTouches(touches);   
		
        IwGxFlush();
        IwGxSwapBuffers();
		
		// Attempt frame rate
		while ((s3eTimerGetMs() - start) < MS_PER_FRAME)
		{
			int32 yield = (int32) (MS_PER_FRAME - (s3eTimerGetMs() - start));
			if (yield < 0) {
				break;
			}
				
			s3eDeviceYield(yield);
		}
	}
    
    s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB);
    s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)MultiTouchButtonCB);

	s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB);
	s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB);
    
	delete game;
	delete localPlayer;
	delete mat;
    palateGroup->Finalise();
    
    for(int i = 0; i < MAX_TOUCHES; ++i)
        if(touches[i].unit)
            delete touches[i].unit;
}

int main() {
	IwGxInit();
	IwResManagerInit();
 
	doMain();
	
	IwResManagerTerminate();
	IwGxTerminate();
		
	return 0;
}
