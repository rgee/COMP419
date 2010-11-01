#include "s3e.h"
#include "artist.h"
#include "uimanager.h"
#include "dummyunit.h"
#include "IwUtil.h"

void doMain() {
	
	CIwArray<GridCell*> cells;
	UIManager ui;
	GridCell gc;
	DummyUnit d1(10, 10);
	DummyUnit d2(40, 40);
	DummyUnit d3(70, 25);

	gc.addUnit(&d1);
	gc.addUnit(&d2);
	gc.addUnit(&d3);
	
	cells.push_back(&gc);
    Artist artist(NULL, &ui);
	artist.updateChangeList(&cells);
    	
	while (1) {
		
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		
		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) || (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
			|| (s3eDeviceCheckQuitRequest())) {
			
		    break;
		}
		
		ui.updateOffset();
		artist.render(5);
		
	}
}

//dummy main function, just so I can test Artist's render() method
int main() {
	
	Iw2DInit();
	
	doMain();
	
	Iw2DTerminate();
	
	return 0;
}
 
