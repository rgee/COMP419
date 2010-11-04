#include "s3e.h"
#include "s3eDebug.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "artist.h"
#include "uimanager.h"
#include "dummyunit.h"


#define FRAME_RATE 60
#define	MS_PER_FRAME (1000 / 60)

void doMain() {
	
	CIwArray<GridCell*> cells;
	UIManager ui;
	GridCell gc;
	DummyUnit d1(10, 10);
	DummyUnit d2(40, 50);
	DummyUnit d3(70, 100);

	gc.addUnit(&d1);
	gc.addUnit(&d2);
	gc.addUnit(&d3);
	
	cells.push_back(&gc);
    Artist artist(NULL, &ui);
	artist.updateChangeList(&cells);
    	
	int curFrame = 0;
	
	while (1) {
		
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		
		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) || (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
			|| (s3eDeviceCheckQuitRequest())) {
			
		    break;
		}
		
		int64 start = s3eTimerGetMs();
		
		ui.updateOffset();
		artist.render(curFrame);
		
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
	
	IwGxInit();
	IwResManagerInit();
	
	doMain();
	
	IwResManagerTerminate();
	IwGxTerminate();
	
	return 0;
}
 
