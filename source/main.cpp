#include "s3e.h"
#include "s3eDebug.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "IwGeomMat.h"
#include "artist.h"
#include "uimanager.h"
#include "unit.h"
#include "muncher.h"

#define FRAME_RATE 10
#define	MS_PER_FRAME (1000 / 10)

CIwSVec2 anim_xy[4];

CIwSVec2 cel_UVs[4];

void doMain() {
	
	IwGetResManager()->LoadGroup("resource_groups/sprites.group");
	CIwResGroup* res = IwGetResManager()->GetGroupNamed("Sprites");
	
	CIwTexture* muncherTex = (CIwTexture*)res->GetResNamed("muncher_sprite_sheet", IW_GX_RESTYPE_TEXTURE);
	CIwMaterial* muncherMat = new CIwMaterial();
	muncherMat->SetTexture(muncherTex);
	muncherMat->SetModulateMode(CIwMaterial::MODULATE_NONE);
	muncherMat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);

	Game* game;
	Player* player;
	
	Unit* munch = new Muncher(player, game, CIwVec2(300, 50)); 
	//Unit* munch1 = new Muncher(player, game, CIwVec2(180, 180)); 
	//Unit* munch2 = new Muncher(player, game, CIwVec2(40, 40)); 
	
	//set up the view transform
	IwGxSetPerspMul(0xa0);
	IwGxSetFarZNearZ(0x1000, 0x10);
	CIwMat view = CIwMat::g_Identity;
	view.SetTrans(CIwVec3(300, 1, -0xa0));
	IwGxSetViewMatrix(&view);

	while (1) {
	
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		
		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
				|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
				|| (s3eDeviceCheckQuitRequest())) {
			
		    break;
		}
		
		IwGxSetColClear(255, 255, 255, 255);
		IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
		
		IwGxLightingOff();
		IwGxSetMaterial(muncherMat);
		
		munch->update();
		//munch1->update();
		//munch2->update();
		
		munch->display();
		//munch1->display();
		//munch2->display();
		
		IwGxFlush();
		IwGxSwapBuffers();
		
		int64 start = s3eTimerGetMs();
		
		// Attempt frame rate
		while ((s3eTimerGetMs() - start) < MS_PER_FRAME)
		{
			int32 yield = (int32) (MS_PER_FRAME - (s3eTimerGetMs() - start));
			if (yield < 0) {
				break;
			}
				
			s3eDeviceYield(yield);
		}
	}
	
	delete muncherMat;
	delete munch;
	//delete munch1;
	//delete munch2;
}

int main() {
	
	IwGxInit();
	IwResManagerInit();
	
	doMain();
	
	IwResManagerTerminate();
	IwGxTerminate();
		
	return 0;
}
 
