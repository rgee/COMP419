#include "s3e.h"
#include "IwUtil.h"
#include "IwGx.h"
#include "IwGeomMat.h"
#include "unit.h"
#include "muncher.h"

#define	MS_PER_FRAME (1000 / 10)

void doMain() {

    IwGetResManager()->LoadGroup("resource_groups/palate.group");
    CIwResGroup* palateGroup = IwGetResManager()->GetGroupNamed("Palate");
    CIwMaterial* mat = new CIwMaterial();
    mat->SetTexture((CIwTexture*)palateGroup->GetResNamed("palate", IW_GX_RESTYPE_TEXTURE));
    mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
    mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
        
	static CIwSVec2 xy(280, 0);
	static CIwSVec2 wh(40, 480);
	static CIwSVec2 uv(0, 0);
	static CIwSVec2 duv(1 << 11, 1 << 11);

    
	Game* game = new Game(2);
	Muncher *munch = new Muncher(NULL, game, CIwVec2(300, 0));
	game->addUnit(munch);
	
	while (1) {
	
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		
		if ((s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
				|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)       
				|| (s3eDeviceCheckQuitRequest())) {
			
		    break;
		}
        
        IwGxSetMaterial(mat);
        IwGxSetScreenSpaceSlot(-1);
        IwGxDrawRectScreenSpace(&xy, &wh, &uv, &duv);
		
        IwGxSetColClear(255, 255, 255, 255);
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
        
		game->tick();
		
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
	
	delete game;
	delete munch;
}

int main() {
	IwGxInit();
	IwResManagerInit();
 
	doMain();
	
	IwResManagerTerminate();
	IwGxTerminate();
		
	return 0;
}
 
