#ifndef _MAIN_H
#define _MAIN_H

#include "s3e.h"
#include "s3eDebug.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "IwGeomMat.h"

#include "game.h"

#include "muncher.h"
#include "shooter.h"
#include "wrecker.h"
#include "spreader.h"
#include "thrower.h"
#include "leader.h"

//run at 60 fps, but only update the game at 12fps
#define	MS_PER_FRAME (1000 / 60)
#define FRAMES_PER_UPDATE 5

int frameCount;

enum gesture_t { CREATE_UNIT, DRAG_WORLD };

// Structure to track touches.
struct CTouch {
    gesture_t gesture_type; // type of gesture activated by this touch
	int32 x;	        	// position
	int32 y;	        	// position
	bool active;        	// whether touch is currently active
	int32 id;	         	// touch's unique identifier
    Unit* unit;             // unit created by this touch if it's a create_unit gesture
	int32 last_x;			// previous x position of a world_drag gesture
    int32 last_y;           // previous y position of a world_drag gesture
};

Game* game = NULL;
Player* localPlayer = NULL;
Player* opponentPlayer = NULL;

#define MAX_TOUCHES 10
CTouch touches[MAX_TOUCHES];

float worldScrollSpeed = 0;

float getAngleDiff(int32 x0, int32 y0, int32 x1, int32 y1);
float getAngleDiff(CTouch* touch);

// find an active touch with the specified id, or allocate a free one from the list.
CTouch* GetTouch(int32 id);

int ui_texture_index = 0;

bool renderTouches(CTouch touches[]);
bool renderUnitCreation(CTouch* touch);
bool renderDragUnit(CTouch* touch);

void giveWorldInitialScrollingSpeed(CTouch* touch);

void MultiTouchButtonCB(s3ePointerTouchEvent* event);
void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event);

void SingleTouchButtonCB(s3ePointerEvent* event);
void SingleTouchMotionCB(s3ePointerMotionEvent* event);

void doMain();
int main();

#endif
