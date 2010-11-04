#include "artist.h"
#include "game.h"

Artist::Artist(Game* _game, UIManager* _ui) : game(_game), ui(_ui) {
	IwGxInit();
	IwGxSetPerspMul(0xa0);
	IwGxSetFarZNearZ(0x400, 0x10);
	current_material = new CIwMaterial;
}

Artist::~Artist(){
	delete current_material;
	delete current_texture;
	IwGxTerminate();
}

void Artist::set_resources(CIwResGroup& new_resources) {
	resources = &new_resources;
}

void Artist::updateChangeList(CIwArray<GridCell*>* _changeList) {
    changeList = _changeList;
}

void Artist::render(int frameNumber) {
	IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

	CIwArray<Unit*> units = *game->getUnits();

	static CIwSVec2* pCoord = IW_GX_ALLOC(CIwSVec2, 4);
	pCoord[0].x = 0x10; pCoord[0].y = 0x30;
	pCoord[1].x = 0x10; pCoord[1].y = 0x60;
	pCoord[2].x = 0x40; pCoord[2].y = 0x30;
	pCoord[3].x = 0x40; pCoord[3].y = 0x60;

	static CIwSVec2 uvs[4] =
	{
		CIwSVec2(0 << 12, 0 << 12),
		CIwSVec2(0 << 12, 1 << 12),
		CIwSVec2(1 << 12, 0 << 12),
		CIwSVec2(1 << 12, 1 << 12),
	};

	IwGxSetScreenSpaceOrg(&CIwSVec2::g_Zero);
	IwGxSetScreenSpaceSlot(-1);

	for(CIwArray<Unit*>::iterator itr = units.begin(); itr != units.end(); ++itr) {
		current_texture = (CIwTexture*)resources->GetResNamed((*itr)->get_tex_name(), IW_GX_RESTYPE_TEXTURE);
		
		if(current_texture) {
			current_material->SetTexture(current_texture);
			current_material->SetColAmbient(255,255,255,255);
		}

		IwGxSetMaterial(current_material);		
		
		IwGxSetVertStreamScreenSpace(pCoord, 4);
		IwGxSetUVStream(uvs);

		IwGxDrawPrims(IW_GX_TRI_STRIP, NULL, 4);
	}

	current_texture = NULL;

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