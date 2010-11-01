#include "artist.h"
#include "game.h"

Artist::Artist(Game* _game, UIManager* _ui) : game(_game), ui(_ui) {

}

Artist::~Artist(){

}

void Artist::updateChangeList(CIwArray<GridCell*> _changeList) {
    changeList = _changeList;
}

void Artist::render() {
    
    //for(CIwArray<GridCell*>::iterator gc_it = changeList.begin(); gc_it != changeList.end(); ++gc_it) {
//        
//        std::set<Unit*> units = (*gc_it)->getUnits();
//        
//        for(std::set<Unit*>::iterator u_it= units.begin(); u_it != units.end(); ++u_it) {
//            (*u_it)->display();
//        }
//    }
	
	int bgColor = 0xffffffff;
	int worldColor = 0xff0000ff;
	
	int surfaceHeight = Iw2DGetSurfaceHeight();
	int surfaceWidth = Iw2DGetSurfaceWidth();
	
	Iw2DSurfaceClear(bgColor);

	CIwSVec2 arcCenter = CIwSVec2(0, surfaceHeight/2);
	int fillWidth = surfaceWidth/1.5;
	int fillHeight = surfaceHeight/2.2;
	CIwSVec2 fillSize = CIwSVec2(fillWidth, fillHeight);
	CIwSVec2 cutOutSize = CIwSVec2(fillWidth/3.0, fillHeight/3.0);

	Iw2DSetColour(worldColor);
	Iw2DFillArc(arcCenter, fillSize, 0, 0x800);
	
	Iw2DSetColour(bgColor);
	Iw2DFillArc(arcCenter, cutOutSize, 0, 0x800);
	
	Iw2DSurfaceShow();
}
