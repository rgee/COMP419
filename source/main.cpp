#include "s3e.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "IwGeomMat.h"
#include "uimanager.h"
#include "unit.h"
#include "muncher.h"

#define FRAME_RATE 10
#define	MS_PER_FRAME (1000 / 10)

void doMain() {

	Game* game = new Game(2);
	Muncher *munch = new Muncher(NULL, game, CIwVec2(300, 0));
	game->addUnit(munch);
	
	while (1) {
	
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		
		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
				|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
				|| (s3eDeviceCheckQuitRequest())) {
			
		    break;
		}
		
		game->render();
		game->tick();
		
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
	}
	
	delete game;
	delete munch;
}

int main() {
	
	IwGxInit();
	IwResManagerInit();
	
	doMain();
	
	IwResManagerTerminate();
	IwGxTerminate();
		
	return 0;
}
 
