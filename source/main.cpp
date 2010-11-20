#include "s3e.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "IwGeomMat.h"
#include "unit.h"
#include "muncher.h"

#define FRAME_RATE 10
#define	MS_PER_FRAME (1000 / 10)

// Structure to track touches.
struct CTouch {
	int32 x;		// position
	int32 y;		// position
	bool active;	// whether touch is currently active
	int32 id;		// touch's unique identifier
};

Game* g_game = NULL;
bool g_UseMultiTouch = false;
//Button* g_MultitouchButton = 0;
char g_TouchEventMsg[128] = {0};

#define MAX_TOUCHES 10
CTouch g_Touches[MAX_TOUCHES];

// find an active touch with the specified id, or allocate a free one from the list.
CTouch* GetTouch(int32 id) {
	CTouch* pInActive = NULL;

	for(uint32 i=0; i < MAX_TOUCHES; i++) {
		// if we've found a touch with the specified id, return its memory address.
		if(id == g_Touches[i].id) return &g_Touches[i];
		// if no touches are found with the id, pInActive will end up being set to
		// last touch in g_Touches.
		if(!g_Touches[i].active) pInActive = &g_Touches[i];
	}

	// return last inactive touch and assign its id to the specified id.
	if (pInActive) {
		pInActive->id = id;
		return pInActive;
	}

	// no more touches; give up.
	return NULL;
}

// assign activity and position info to the touch struct associated with an event
// for a multitouch click.
void MultiTouchButtonCB(s3ePointerTouchEvent* event) {
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch) {
		touch->active = event->m_Pressed != 0;
		touch->x = event->m_x;
		touch->y = event->m_y;
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

// assign activity and position info to the touch struct for a singletouch click
// and print info about activity of click.
void SingleTouchButtonCB(s3ePointerEvent* event) {
	g_Touches[0].active = event->m_Pressed != 0;
	g_Touches[0].x = event->m_x;
	g_Touches[0].y = event->m_y;

	sprintf(g_TouchEventMsg, "`x666666Touch %s", event->m_Pressed ? "PRESSED" : "RELEASED" );
}

// assign position info to the touch struct for a singletouch motion event.
void SingleTouchMotionCB(s3ePointerMotionEvent* event) {
	g_Touches[0].x = event->m_x;
	g_Touches[0].y = event->m_y;
}

void registerMultitouchCallbacks() {
	s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);
	s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);
}

void unregisterMultitouchCallbacks() {
	s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB);
	s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB);
}

void registerSingletouchCallbacks() {
	s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
	s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);
}

void unregisterSingletouchCallbacks() {
	s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB);
	s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB);
}

void init() {
	g_UseMultiTouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;
	
	if (g_UseMultiTouch) {
		registerMultitouchCallbacks();
		//g_MultiTouchButton = NewButton("Disable Multitouch");
	} else {
		registerSingletouchCallbacks();
	}

	Game* game = new Game(2);
}

void shutDown() {
	if (g_UseMultiTouch) {
		unregisterMultitouchCallbacks();
	} else {
		unregisterSingletouchCallbacks();
	}
}

bool update() {
	/*if (g_MultiTouchButton && g_MultiTouchButton == GetSelectedButton()) {
		DeleteButtons();

		if (g_UseMultiTouch) {
			g_MultiTouchButton = NewButton("Enable Multitouch");
			unregisterMultitouchCallbacks();
			registerSingletouchCallbacks();
		} else {
			g_MultiTouchButton = NewButton("Disable Multitouch");
			unregisterSingletouchCallbacks();
			registerMultitouchCallbacks();
		}

		g_UseMultiTouch = !g_UseMultiTouch;
	}*/

	return true;
}

void renderTouch(int32 x, int32 y) {
	Muncher* munch = new Muncher(NULL, g_game, CIwVec2(x,y));
	g_game->addUnit(munch);
}

void render() {
	for(uint32 i=0; i < MAX_TOUCHES; i++) {
		// for each active touch render a muncher.
		if(g_Touches[i].active)	renderTouch(g_Touches[i].x, g_Touches[i].y);
	}

	g_game->render();
	g_game->tick();
}


void doMain() {
	init();

	while (1) {
		s3eDeviceYield(0);
		s3eKeyboardUpdate();

		if ( (! update()) ||
			(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) ||
			(s3eKeyboardGetState(s3eKeyLSK) & S3E_KEY_STATE_DOWN) ||
			(s3eDeviceCheckQuitRequest()) )       break;

		render();
	}

	shutDown();
}

int main() {
	
	IwGxInit();
	IwResManagerInit();
	
	doMain();
	
	IwResManagerTerminate();
	IwGxTerminate();
		
	return 0;
}
 