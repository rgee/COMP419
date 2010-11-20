#include "game.h"
#include "unit.h"
 
Game::Game(int numPlayers) : numPlayers(numPlayers), numUnits(0) {
	//ai = AI();
	IwGetResManager()->LoadGroup("resource_groups/game.group");
	resources = IwGetResManager()->GetGroupNamed("Sprites");
	initRenderState();
}

Game::~Game(){
    	
	for (UnitBucket::iterator itr = unitBucket.begin(); itr != unitBucket.end(); ++itr) {
		(*itr).second->clear();
		delete (*itr).second;
	}
	
	units.clear();
	unitBuffer.clear();
}

void Game::initRenderState() {
	
	//set up the camera position and view transform
	IwGxSetPerspMul(0x9);
	IwGxSetFarZNearZ(0xa, 0x8);
	CIwMat view = CIwMat::g_Identity;
	view.SetTrans(CIwVec3(300, 0, -0x9));
	IwGxSetViewMatrix(&view);
}

std::list<Unit*>* Game::getUnits(){
	return &units;
}

void Game::addUnit(Unit *u){
	
    u->setId(numUnits++);

	if(units.empty()) {
		units.push_back(u);
	} else {
		unitBuffer.push_back(u);
	}
	
	if(unitBucket.find(u->getTextureName()) == unitBucket.end()) {
		std::set<Unit*>* bucket = new std::set<Unit*>();
		bucket->insert(u);
		unitBucket[u->getTextureName()] = bucket;
	}
	else {
		(unitBucket[u->getTextureName()])->insert(u);
	}
}

void Game::tick(){

	float curr_theta, new_theta;
	for(std::list<Unit*>::iterator itr = units.begin(); itr !=units.end(); ++itr) {
		(*itr)->update();
		curr_theta = (*itr)->getTheta();
		for(std::list<Unit*>::iterator new_itr = unitBuffer.begin(); new_itr != unitBuffer.end(); ++new_itr) {

			new_theta = (*new_itr)->getTheta();

			if( (curr_theta < new_theta)) { //|| (new_theta <= (*(++itr))->getTheta())) {
				units.insert((++itr), (*new_itr));
				unitBuffer.erase(new_itr);
				//break;
			}
		}
	}
	
    ++timesteps;
	render();
}

void Game::render() {
	
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
	delete mat;
	
	IwGxSwapBuffers();
}

CIwFVec2 Game::getWorldRadius() {
	return CIwFVec2(innerRadius, outerRadius);
}