#include "mainmenu.h"

MainMenu::MainMenu() {
    IwGetResManager()->LoadGroup("resource_groups/mainmenu.group");
    images = IwGetResManager()->GetGroupNamed("mainmenu");
    
    mat.SetTexture((CIwTexture*)images->GetResNamed("menu_bg", IW_GX_RESTYPE_TEXTURE));
    mat.SetModulateMode(CIwMaterial::MODULATE_NONE);
	mat.SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
}

MainMenu::~MainMenu() {
    images->Finalise();
}

void MainMenu::initRenderState() {
    //set up the camera position and view transform
    int w = IwGxGetScreenWidth();

	IwGxSetPerspMul(9);
	IwGxSetFarZNearZ(12, 8);
	view = CIwMat::g_Identity;
	IwGxSetViewMatrix(&view);
}

void MainMenu::tick() {

}

void MainMenu::render() {
	IwGxSetMaterial(&mat);
	renderImageWorldSpace(CIwFVec2::g_Zero, 0.0, 0.85, 960, 0, 0, 1, 0.0f);
}