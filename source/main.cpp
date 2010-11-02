#include "s3e.h"
#include "artist.h"
#include "IwGx.h"
#include <stdio.h>

CIwMaterial* material;
CIwTexture* texture = NULL;
CIwResGroup* group;

void render_billboard(){
	if(!texture) {
		/*
		texture = new CIwTexture;
		texture->LoadFromFile("disc.bmp");
		texture->Upload();
		*/
		IwGetResManager()->LoadGroup("map.group");
		group = IwGetResManager()->GetGroupNamed("Map");
		texture = (CIwTexture*)group->GetResNamed("disc", IW_GX_RESTYPE_TEXTURE);

	}

	if(texture) {
		IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

		material->SetTexture(texture);
		material->SetColAmbient(255, 255, 255, 255);

		IwGxSetMaterial(material);

		// Vertex colours
		static CIwColour s_Cols[8] =
		{
			{0xff, 0x00, 0x00, 0x00},
			{0xff, 0xff, 0x00, 0x00},
			{0x00, 0xff, 0xff, 0x00},
			{0x00, 0x00, 0xff, 0x00},
			{0xff, 0x00, 0xff, 0x00},
			{0xff, 0x00, 0x00, 0x00},
			{0xff, 0xff, 0x00, 0x00},
			{0x00, 0xff, 0xff, 0x00},
		};


		static CIwSVec2* pCoord = IW_GX_ALLOC(CIwSVec2, 4);
		pCoord[0].x = 0x10; pCoord[0].y = 0x30;
		pCoord[1].x = 0x10; pCoord[1].y = 0x60;
		pCoord[2].x = 0x40; pCoord[2].y = 0x30;
		pCoord[3].x = 0x40; pCoord[3].y = 0x60;

		IwGxSetScreenSpaceOrg(&CIwSVec2::g_Zero);
		IwGxSetScreenSpaceSlot(-1);

		IwGxSetVertStreamScreenSpace(pCoord, 4);
		//IwGxSetColStream(s_Cols, 8);

		static CIwSVec2 uvs[4] =
		{
			CIwSVec2(0 << 12, 0 << 12),
			CIwSVec2(0 << 12, 1 << 12),
			CIwSVec2(1 << 12, 1 << 12),
			CIwSVec2(1 << 12, 0 << 12),
		};
		IwGxSetUVStream(uvs);

		IwGxDrawPrims(IW_GX_TRI_STRIP, NULL, 4);

	}
	IwGxFlush();
	IwGxSwapBuffers();
}

void init(){
	IwGxInit();
	IwResManagerInit();

	IwGetResManager()->SetMode(CIwResManager::MODE_BUILD);

	IwGxSetPerspMul(0xa0);
	IwGxSetFarZNearZ(0x400, 0x10);
	material = new CIwMaterial;
}

void shutdown(){
	delete material;
	
	IwResManagerTerminate();
	IwGxTerminate();
}

//dummy main function, just so I can test Artist's render() method
int main() {
	

	init();

 //	Iw2DInit();
	//Game game = Game(2, 800, 600);

	while (1) {
		
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();

		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) || (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
		     || (s3eDeviceCheckQuitRequest())) {
		         
		    break;
		}
		render_billboard();
		/*game.tick();*/
	}
	/*Iw2DTerminate();*/

	shutdown();
	
	return 0;
}

 
