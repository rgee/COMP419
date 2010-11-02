#include "s3e.h"
#include "s3eDebug.h"
#include "artist.h"
#include "uimanager.h"
#include "dummyunit.h"
#include <stdio.h>
#include <stdarg.h>
#include "IwUtil.h"

#define FRAME_RATE 30
#define	MS_PER_FRAME (1000 / 30)

void doMain() {
	
	Game game = Game(2);
    
    CIw2DImage* img = Iw2DCreateImage("pacman-01.bmp");
    
	CIwArray<GridCell*> cells;
	GridCell gc;
	DummyUnit d1(NULL, &game, CIwVec2(10, 10));

    
	gc.addUnit(d1);

	cells.push_back(&gc);
	
	game.getArtist()->updateChangeList(&cells);
	
    	
	int curFrame = 0;
	while (1) {
		
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		
		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
				|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
				|| (s3eDeviceCheckQuitRequest())) {
			
		    break;
		}

		
		game.tick();
				
		int64 start = s3eTimerGetMs();
		
		// Attempt frame rate
		while ((s3eTimerGetMs() - start) < MS_PER_FRAME)
		{
			int32 yield = (int32) (MS_PER_FRAME - (s3eTimerGetMs() - start));
			if (yield < 0) {
				break;
			}
				
			s3eDeviceYield(yield);
		}
		
		if(curFrame >= FRAME_RATE) {
			curFrame = 0;
		} 
		else {
			curFrame++;
		}	
	}
}

//dummy main function, just so I can test Artist's render() method
int main() {
	
	Iw2DInit();
	
	doMain();
	
	Iw2DTerminate();
	
	return 0;
}
 
