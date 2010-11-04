#include "artist.h"

#define DEFAULT_WORLD_WIDTH 480
#define DEFAULT_WORLD_HEIGHT 480
#define DEFAULT_WORLD_X -280

Artist::Artist(Game* _game, UIManager* _ui) : game(_game), ui(_ui) {

	IwGetResManager()->LoadGroup("resource_groups/world.group");
	CIwResGroup* worldRes = IwGetResManager()->GetGroupNamed("World");
	
	CIwTexture* worldTexture = (CIwTexture*)worldRes->GetResNamed("paper-world", IW_GX_RESTYPE_TEXTURE);
	worldMaterial = new CIwMaterial();
	worldMaterial->SetModulateMode(CIwMaterial::MODULATE_NONE);
	worldMaterial->SetTexture(worldTexture);
	
}

Artist::~Artist() {
	delete worldMaterial;
}
	
void Artist::updateChangeList(CIwArray<GridCell*>* _changeList) {
    changeList = _changeList;
}

void Artist::render(int frameNumber) {
	
	int screenWidth = IwGxGetScreenWidth();
	int screenHeight = IwGxGetScreenHeight();
	
	// Set screen clear colour
    IwGxSetColClear(0xff, 0xff, 0xff, 0x00);
    
	// Turn all lighting off
    IwGxLightingOff();
	
	//clear the screen
	IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
	
	IwGxSetScreenSpaceSlot(-1);
	

	//draw the world donut
	IwGxSetMaterial(worldMaterial);
	CIwSVec2 world_wh(DEFAULT_WORLD_WIDTH, DEFAULT_WORLD_HEIGHT);
	CIwSVec2 world_pos = CIwSVec2(DEFAULT_WORLD_X, 0);
	IwGxDrawRectScreenSpace(&world_pos, &world_wh);
	
	
    /*for(CIwArray<GridCell*>::iterator gc_it = changeList->begin(); gc_it != changeList->end(); ++gc_it) {
       
        std::set<Unit*> units = (*gc_it)->getUnits();
       
        for(std::set<Unit*>::iterator u_it= units.begin(); u_it != units.end(); ++u_it) {
			
			Unit* curUnit = *u_it;
			
			int r = curUnit->getR();
			float theta = curUnit->getTheta();
			
            curUnit->display(r, surfaceHeight - theta - ui->getWorldOffset(), 0x80, frameNumber);
        }
    }*/
	
	
	//char* str;
	//asprintf(&str, "width: %i | height: %i", width, height);	
	//IwGxPrintSetColour(0, 0, 0);
	//IwGxPrintString(10, 10, str);
	
	// Flush and swap
	IwGxFlush();
	IwGxSwapBuffers();
}
