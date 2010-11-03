#include "artist.h"
#include "game.h"

Artist::Artist(Game* _game, UIManager* _ui) : game(_game), ui(_ui) {
	IwGxInit();
	IwResManagerInit();
}

Artist::~Artist(){
	IwResManagerTerminate();
	IwGxTerminate();
}

void Artist::set_resources(CIwResGroup& new_resources) {
	resources = &new_resources;
}

void Artist::updateChangeList(CIwArray<GridCell*>* _changeList) {
    changeList = _changeList;
}

void Artist::render(int frameNumber) {

	IwGxFlush();
	IwGxSwapBuffers();
    
	/*
	int bgColor = 0xffffffff;
	int worldColor = 0xff0000ff;
	
	int surfaceHeight = Iw2DGetSurfaceHeight();
	int surfaceWidth = Iw2DGetSurfaceWidth();
	
	Iw2DSurfaceClear(bgColor);
	
	CIwSVec2 topLeft = CIwSVec2(0, 0);
	CIwSVec2 size = CIwSVec2(surfaceWidth/2, surfaceHeight);
	
	Iw2DSetColour(worldColor);
	Iw2DFillRect(topLeft, size);
	
    for(CIwArray<GridCell*>::iterator gc_it = changeList->begin(); gc_it != changeList->end(); ++gc_it) {
       
        CIwArray<Unit*> units = (*gc_it)->getUnits();
       
        for(CIwArray<Unit*>::iterator u_it= units.begin(); u_it != units.end(); ++u_it) {
			
			Unit* curUnit = *u_it;
			
			int r = curUnit->getR();
			float theta = curUnit->getTheta();
			
            //curUnit->display(r, surfaceHeight - theta - ui->getWorldOffset(), 0x80, frameNumber);

			curUnit->display();
        }
    }
	
	Iw2DSurfaceShow();
	*/
}
