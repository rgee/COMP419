#include "s3e.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "IwGeomMat.h"
#include "unit.h"
#include "muncher.h"

#define	MS_PER_FRAME (1000 / 10)

// Structure to track touches.
struct CTouch {
	int32 x;		// position
	int32 y;		// position
	bool active;	// whether touch is currently active
	int32 id;		// touch's unique identifier
};

Game* game = NULL;

#define MAX_TOUCHES 10
CTouch touches[MAX_TOUCHES];

// find an active touch with the specified id, or allocate a free one from the list.
CTouch* GetTouch(int32 id) {
	CTouch* pInActive = NULL;
    
	for(uint32 i=0; i < MAX_TOUCHES; i++) {
		// if we've found a touch with the specified id, return its memory address.
		if(id == touches[i].id) return &touches[i];
		// if no touches are found with the id, pInActive will end up being set to
		// last touch in g_Touches.
		if(!touches[i].active) pInActive = &touches[i];
	}
    
	// return last inactive touch and assign its id to the specified id.
	if (pInActive) {
		pInActive->id = id;
		return pInActive;
	}
    
	// no more touches; give up.
	return NULL;
}


bool update() {    
	return true;
}

void renderTouch(int32 x, int32 y) {
	Muncher* munch = new Muncher(NULL, game, CIwVec2(x,y));
	game->addUnit(munch);
}


// assign activity and position info to the touch struct associated with an event
// for a multitouch click.
void MultiTouchButtonCB(s3ePointerTouchEvent* event) {
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch) {
		touch->active = event->m_Pressed != 0;
		touch->x = event->m_x;
		touch->y = event->m_y;
        renderTouch(touch->x, touch->y);
	}
}

// assign position info to the touch struct associated with an event for
// multitouch motion.
void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event) {
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch) {
		touch->x = event->m_x;
		touch->y = event->m_y;
	}
}

void doMain() {
    
    s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);
    s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);

	s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);
    s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);

    
    IwGetResManager()->LoadGroup("resource_groups/palate.group");
    CIwResGroup* palateGroup = IwGetResManager()->GetGroupNamed("Palate");
    CIwMaterial* mat = new CIwMaterial();
    mat->SetTexture((CIwTexture*)palateGroup->GetResNamed("palate", IW_GX_RESTYPE_TEXTURE));
    mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
    mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
        
	static CIwSVec2 xy(280, 0);
	static CIwSVec2 wh(40, 480);
	static CIwSVec2 uv(0, 0);
	static CIwSVec2 duv(1 << 11, 1 << 11);

    
	game = new Game(2);
	Muncher *munch = new Muncher(NULL, game, CIwVec2(300, 0));
	Muncher *munch2 = new Muncher(NULL, game, CIwVec2(300, 0));
	game->addUnit(munch);
	game->addUnit(munch2);
	
	while (1) {
	
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		
		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
				|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
				|| (s3eDeviceCheckQuitRequest())) {
			
		    break;
		}
        
        IwGxSetMaterial(mat);
        IwGxSetScreenSpaceSlot(-1);
        IwGxDrawRectScreenSpace(&xy, &wh, &uv, &duv);
		
        IwGxSetColClear(255, 255, 255, 255);
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
        
        game->tick();
		
		int64 start = s3eTimerGetMs();
        
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
	delete munch;
	delete munch2;
}

int main() {
	IwGxInit();
	IwResManagerInit();
 
	doMain();
	
	IwResManagerTerminate();
	IwGxTerminate();
		
	return 0;
}
