#include "game.h"
#include "unit.h"

Game::Game(int numPlayers) : numPlayers(numPlayers) {
	IwResManagerInit();
	IwGetResManager()->SetMode(CIwResManager::MODE_BUILD);
	IwGetResManager()->LoadGroup("main.group");

	resources = IwGetResManager()->GetGroupNamed("main");
}

Game::~Game(){
	IwGetResManager()->DestroyGroup("main");
	IwResManagerTerminate();
}

CIwArray<Unit*>* Game::getUnits(){
	return &units;
}

void Game::addUnit(Unit *u){
    u->setId(units.size());
    units.push_back(u);
}

void Game::tick(){

	for(CIwArray<Unit*>::iterator itr = units.begin(); itr != units.end(); ++itr){
		(*itr)->update();
	}
	
	ui_manager->updateOffset();
    ++timesteps;
}