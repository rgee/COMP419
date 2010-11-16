#include "s3e.h"
#include "s3eDebug.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "IwGeomMat.h"
#include "artist.h"
#include "uimanager.h"
#include "unit.h"
#include "muncher.h"

#define FRAME_RATE 10
#define	MS_PER_FRAME (1000 / 10)

CIwSVec2 anim_xy[4];

CIwSVec2 cel_UVs[4];

void doMain() {

	Game* game = new Game(2);
	
	/*for(int x = 64; x < 320; x+= 64) {
		for (int y = 64; y < 480; y+= 64) {
			game->addUnit(new Muncher(NULL, game, CIwVec2(140+x, y-240)));
		}
	}*/
	
	Muncher *munch = new Muncher(NULL, game, CIwVec2(300, 200));
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
	
	delete munch;
	delete game;
}

int main() {
	
	IwGxInit();
	IwResManagerInit();
	
	doMain();
	
	IwResManagerTerminate();
	IwGxTerminate();
		
	return 0;
}
 
