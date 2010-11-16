#include "game.h"
#include "unit.h"

Game::Game(int numPlayers) : numPlayers(numPlayers) {
	IwGetResManager()->LoadGroup("resource_groups/game.group");
	resources = IwGetResManager()->GetGroupNamed("Sprites");
	initRenderState();
}

Game::~Game(){
		
	for (UnitBucket::iterator itr = unitBucket.begin(); itr != unitBucket.end(); ++itr) {
		(*itr).second->clear();
		delete (*itr).second;
	}
	
	units.clear_optimised();
}

void Game::initRenderState() {
	//set up the view transform
	IwGxSetPerspMul(0xa0);
	IwGxSetFarZNearZ(0x1000, 0x10);
	CIwMat view = CIwMat::g_Identity;
	view.SetTrans(CIwVec3(300, 1, -0xa0));
	IwGxSetViewMatrix(&view);
}

CIwArray<Unit*>* Game::getUnits(){
	return &units;
}

void Game::addUnit(Unit *u){
	
    u->setId(units.size());
    units.push_back(u);
	
	if(unitBucket.find(u->getTextureName()) == unitBucket.end()) {
		CIwMaterial* mat = new CIwMaterial();
		mat->SetTexture((CIwTexture*)resources->GetResNamed(u->getTextureName(), IW_GX_RESTYPE_TEXTURE));
		mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
		mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
		std::set<Unit*>* bucket = new std::set<Unit*>();
		bucket->insert(u);
		unitBucket[u->getTextureName()] = bucket;
	}
	else {
		(unitBucket[u->getTextureName()])->insert(u);
	}
}

void Game::tick(){

	for(CIwArray<Unit*>::iterator itr = units.begin(); itr != units.end(); ++itr){
		(*itr)->update();
	}
	
    ++timesteps;
	render();
}

void Game::render() {
	
	IwGxSetColClear(255, 100, 255, 255);
	IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
	
	char* curTexture = "";
	CIwMaterial* mat = new CIwMaterial();
	
	for (UnitBucket::iterator itr = unitBucket.begin(); itr != unitBucket.end(); ++itr) {
		
		if (strcmp((*itr).first, curTexture) != 0) {
			curTexture = (*itr).first;
			mat->SetTexture((CIwTexture*)resources->GetResNamed(curTexture, IW_GX_RESTYPE_TEXTURE));
			mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
			mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
			IwGxSetMaterial(mat);
		}
		
		std::set<Unit*>* renderUnits = (*itr).second;
		
		for (std::set<Unit*>::iterator u_it = renderUnits->begin(); u_it != renderUnits->end(); ++u_it) {
			(*u_it)->display();
		}
	}
	
	IwGxSwapBuffers();
	
	delete(mat);
}