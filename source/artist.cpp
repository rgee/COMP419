#include "artist.h"

Artist::Artist(Game* _game, UIManager* _ui) : game(_game), ui(_ui) {};

void Artist::updateChangeList(CIwArray<GridCell*>* _changeList) {
    changeList = _changeList;
}

void Artist::render(int frameNumber) {
    
	
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
       
        std::set<Unit*> units = (*gc_it)->getUnits();
       
        for(std::set<Unit*>::iterator u_it= units.begin(); u_it != units.end(); ++u_it) {
			
			Unit* curUnit = *u_it;
			
			int r = curUnit->getR();
			float theta = curUnit->getTheta();
			
            curUnit->display(r, surfaceHeight - theta - ui->getWorldOffset(), 0x80, 5);
        }
    }
	
	Iw2DSurfaceShow();
}
