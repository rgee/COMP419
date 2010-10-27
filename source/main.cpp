#include "s3e.h"
#include "artist.h"
#include "IwUtil.h"

//dummy main function, just so I can test Artist's render() method
int main() {
	
	Iw2DInit();
	
	CIwArray<GridCell*> cells;
	GridCell gc;
	cells.push_back(&gc);
    Artist artist(NULL, NULL);
	artist.updateChangeList(&cells);
    
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
 
