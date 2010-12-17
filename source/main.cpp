#include "main.h"

//bool ExampleUpdate();
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

bool renderTouches() {
    bool all_active = true;
    bool successful_so_far = true;

	for(int i = 0; i < MAX_TOUCHES; ++i) {
        if(touches[i].active) {
            if(touches[i].gesture_type == CREATE_UNIT) {
                successful_so_far &= renderDragUnit(&touches[i]);
			}
		}else {
            all_active = false;
        }

	}
    
    if(all_active){
        
    }

	return successful_so_far;
}

bool renderUnitCreation(CTouch* touch) {
    if(!touch->unit)
        return false;
    
    CIwFVec2 radii = game->getWorldRadius();
    CIwFVec2 modelCoords = worldify(touch->x, touch->y, radii.x, game->getRotation());
    
    float dist_sq = SQ(modelCoords.x) + SQ(modelCoords.y);
    if(dist_sq > SQ(radii.y) || dist_sq < SQ(radii.x)){
        delete touch->unit;
        return false;
    }
    
    touch->unit->setPosition(modelCoords);
	game->addUnit(touch->unit, false);
    
    touch->unit = NULL;
    touch->active = false;
    
    return true;
}

bool renderDragUnit(CTouch* touch){
	if (!touch->unit) return false;
	else {
        touch->unit->displayOnScreen(touch->x, touch->y);
		return true;
	}
}

float getAngleDiff(int32 x0, int32 y0, int32 x1, int32 y1) {
	if (y0 != y1 || x0 != x1) {
		float inner_radius = game->getWorldRadius().x;
		CIwFVec2 start_pos_world = worldify(x0, y0, inner_radius, game->getRotation());
		CIwFVec2 end_pos_world = worldify(x1, y1, inner_radius, game->getRotation());

		return 1.25 * angle_diff(start_pos_world, end_pos_world); // Feels a little more realistic
	} else {
		return 0.0;
	}
}

float getAngleDiff(CTouch* touch) {
	return getAngleDiff(touch->last_x, touch->last_y, touch->x, touch->y);
}

// callback called whenever a touch is initiated or ended.
void MultiTouchButtonCB(s3ePointerTouchEvent* event) {
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch) {
        touch->active = event->m_Pressed != 0;
		touch->x = event->m_x;
		touch->y = event->m_y;

        // if it's the beginning of a touch, then determine what kind of gesture it is and set initial info.
        if (touch->active) {
            if (touch->x > (int32) IwGxGetScreenWidth() - 60) {
                touch->gesture_type = CREATE_UNIT;
                int y = touch->y - 94; // Palate offset
                
                if(y < 0) return;
                
                switch (y / 55) {
                    case 0:
                        unit_ui->SetTexture((CIwTexture*)palateGroup->GetResNamed("TAKE2_MINUS_THROWER", IW_GX_RESTYPE_TEXTURE));
                        touch->unit = new Thrower(localPlayer,  game, 0, 0);
                        break;
                    case 1:
                        unit_ui->SetTexture((CIwTexture*)palateGroup->GetResNamed("TAKE2_MINUS_WRECKER", IW_GX_RESTYPE_TEXTURE));
                        touch->unit = new Wrecker(localPlayer,  game, 0, 0);
                        break;
                    case 2: 
                        unit_ui->SetTexture((CIwTexture*)palateGroup->GetResNamed("TAKE2_MINUS_MUNCHER", IW_GX_RESTYPE_TEXTURE));
                        touch->unit = new Muncher(localPlayer,  game, 0, 0);
                        break;
                    case 3:
                        unit_ui->SetTexture((CIwTexture*)palateGroup->GetResNamed("TAKE2_MINUS_SHOOTER", IW_GX_RESTYPE_TEXTURE));
                        touch->unit = new Shooter(localPlayer,  game, 0, 0);
                        break;
                    case 4: 
                        unit_ui->SetTexture((CIwTexture*)palateGroup->GetResNamed("TAKE2_MINUS_SPREADER", IW_GX_RESTYPE_TEXTURE));
                        touch->unit = new Spreader(localPlayer, game, 0, 0);
                        break;
                    default: break;
                }
                   
            } else {
                touch->gesture_type = DRAG_WORLD;
                worldScrollSpeed = 0;
            }
        // if it's the end of a touch, check what kind of gesture it and render.
        } else {
			switch(touch->gesture_type) {
				case CREATE_UNIT:
                    unit_ui->SetTexture((CIwTexture*)palateGroup->GetResNamed("TAKE2", IW_GX_RESTYPE_TEXTURE));
                    renderUnitCreation(touch);
                    break;
				case DRAG_WORLD: /* shouldn't need to do anything */ break;
				default: break;
            }
        }
	}
}

// called whenever a touch is moved.
void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event) {
    if(event->m_x < 0) return;
    
	CTouch* touch = GetTouch(event->m_TouchID);

    if (touch->gesture_type == DRAG_WORLD && touch->active) {
		touch->last_x = touch->x;
        touch->last_y = touch->y;
		touch->x = event->m_x;
        touch->y = event->m_y;
			
		worldScrollSpeed = getAngleDiff(touch);
    } else {
		touch->x = event->m_x;
		touch->y = event->m_y;
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

void init(){
    if(localPlayer) free(localPlayer);
    if(opponentPlayer) free(opponentPlayer);
    if(game) free(game);
    
    CIwColour localCol = {255, 180, 180, 255};
	CIwColour opponentCol = {180, 255, 160, 255};
	
	localPlayer = new Player(localCol);
	opponentPlayer = new GameKitPlayer(opponentCol);
    
    game = new Game(localPlayer, opponentPlayer);
    
    /*opponentPlayer->setGame(game);
    while(!opponentPlayer->connect()){
        s3eDeviceYield(100);
    }*/
    opponentPlayer->setGame(game);
    
    // Presumably, draw something before doing this
    while(s3eExtIPhoneGameKitAvailable() && !opponentPlayer->connect()){
        // Draw a loading thing in here
        s3eDeviceYield();
    }
	
    CIwFVec2 pos(game->getWorldRadius().y + 20, 0);
    polarToXY(pos);
	Leader* localLeader = new Leader(localPlayer, game, pos.x, pos.y);
    pos.x = game->getWorldRadius().y + 20;
    pos.y = PI;
    polarToXY(pos);
	Leader* opponentLeader = new Leader(opponentPlayer, game, pos.x, pos.y);
    
	game->addUnit(localLeader);
	game->addUnit(opponentLeader);
	
	localPlayer->setLeader(localLeader);
	opponentPlayer->setLeader(opponentLeader);
	
    frameCount = 0;
}

void doMain() {
    if(s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE)){
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);
    } else {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);
    }


    IwGetResManager()->LoadGroup("resource_groups/palate.group");
    
    palateGroup = IwGetResManager()->GetGroupNamed("Palate");

    std::vector<int> ui_texture_hashes;
	int background_hash = IwHashString("background_clean");
	CIwResList* resources = palateGroup->GetListHashed(IwHashString("CIwTexture"));
	for(CIwManaged** itr = resources->m_Resources.GetBegin(); itr != resources->m_Resources.GetEnd(); ++itr) {
		if(background_hash != (*itr)->m_Hash) {
			ui_texture_hashes.push_back((*itr)->m_Hash);
		}
	}
    
    CIwMaterial* background = new CIwMaterial();
    background->SetTexture((CIwTexture*)palateGroup->GetResNamed("background_clean", IW_GX_RESTYPE_TEXTURE));
    background->SetModulateMode(CIwMaterial::MODULATE_NONE);
    background->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);

	unit_ui = new CIwMaterial();
    unit_ui->SetModulateMode(CIwMaterial::MODULATE_NONE);
    unit_ui->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
    unit_ui->SetTexture((CIwTexture*)palateGroup->GetResNamed("TAKE2", IW_GX_RESTYPE_TEXTURE));
    
    CIwSVec2 bg_wh(320, 480);
	CIwSVec2 ui_wh(80, 480);
	CIwSVec2 ui_offset(240, 0);
	CIwSVec2 uv(0, 0);
	CIwSVec2 duv(IW_GEOM_ONE, IW_GEOM_ONE);

    init();
    
	IwGxLightingOff();
    IwGxSetColClear(255, 255, 255, 255);
    
    float worldScrollMultiplier = 0.75;
    
    if(s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_IPHONE) {
        worldScrollMultiplier = 0.925;
    }

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
        
        IwGxSetMaterial(background);
        IwGxSetScreenSpaceSlot(-1);
        IwGxDrawRectScreenSpace(&CIwSVec2::g_Zero, &bg_wh, &uv, &duv);

		IwGxSetMaterial(unit_ui);
        IwGxSetScreenSpaceSlot(-1); 
        IwGxDrawRectScreenSpace(&ui_offset, &ui_wh, &uv, &duv);
        
		if (worldScrollSpeed > .0005 || worldScrollSpeed < -.0005) {
			game->rotate(worldScrollSpeed);
            worldScrollSpeed *= worldScrollMultiplier;
		}
	
        if(frameCount % FRAMES_PER_UPDATE == 0) {
			game->tick();
		}
		
		game->render();
		if(!renderTouches()) break;
        		
        IwGxFlush();
        
        IwGxSwapBuffers();
		
		// Attempt frame rate
		while ((s3eTimerGetMs() - start) < MS_PER_FRAME){
			int32 yield = (MS_PER_FRAME - (s3eTimerGetMs() - start));
			if (yield < 0) {
				break;
			}
				
			s3eDeviceYield(yield);
		}
		
		frameCount++;

        
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
	}
    
	delete game;
	delete localPlayer;
	delete opponentPlayer;
    delete background;
	delete unit_ui;
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
