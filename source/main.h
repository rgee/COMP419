#ifndef _MAIN_H
#define _MAIN_H

#include "s3e.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "IwGeomMat.h"

#include "game.h"

#include "muncher.h"
#include "shooter.h"
#include "wrecker.h"
#include "spreader.h"

#define	MS_PER_FRAME (1000 / 12)

enum gesture_t { CREATE_UNIT, DRAG_WORLD };

// Structure to track touches.
struct CTouch {
    gesture_t gesture_type; // type of gesture activated by this touch
	int32 x;	        	// position
	int32 y;	        	// position
	bool active;        	// whether touch is currently active
	int32 id;	         	// touch's unique identifier
    Unit* unit;             // unit created by this touch if it's a create_unit gesture
	int32 start_x;			// initial x position of a world_drag gesture
    int32 start_y;          // initial y position of a world_drag gesture
};

Game* game = NULL;
Player* localPlayer = NULL;
Player* opponentPlayer = NULL;

#define MAX_TOUCHES 10
CTouch touches[MAX_TOUCHES];

// find an active touch with the specified id, or allocate a free one from the list.
CTouch* GetTouch(int32 id);

bool renderTouches(CTouch touches[]);
bool renderUnitCreation(CTouch* touch);
bool renderDragUnit(CTouch* touch);
bool renderDragWorld(CTouch* touch);

// assign activity and position info to the touch struct associated with an event
// for a multitouch click.
void MultiTouchButtonCB(s3ePointerTouchEvent* event);
// assign position info to the touch struct associated with an event for
// multitouch motion.
void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event);

void SingleTouchButtonCB(s3ePointerEvent* event);
void SingleTouchMotionCB(s3ePointerMotionEvent* event);

void doMain();
int main();

#endif
