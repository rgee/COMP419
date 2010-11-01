#include "s3e.h"
#include "artist.h"
#include <stdio.h>

//dummy main function, just so I can test Artist's render() method
int main() {
	

 	Iw2DInit();
	Game game = Game(2, 800, 600);

	while (1) {
		
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();

		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) || (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
		     || (s3eDeviceCheckQuitRequest())) {
		         
		    break;
		}

		game.tick();
	}
	Iw2DTerminate();
	
	return 0;
}
 
