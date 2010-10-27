#include "s3e.h"
#include "artist.h"

//dummy main function, just so I can test Artist's render() method
int main() {
	
	Iw2DInit();
	
    Artist artist(NULL, NULL);
    
	while (1) {
		
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();

		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) || (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
		     || (s3eDeviceCheckQuitRequest())) {
		         
		    break;
		}
		
		artist.render();

	}
	
	Iw2DTerminate();
	
	return 0;
}
 
