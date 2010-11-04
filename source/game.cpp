#include "game.h"
#include "unit.h"
#include "artist.h"

Game::Game(int numPlayers) : numPlayers(numPlayers) {
	ui_manager = new UIManager();
	artist = new Artist(this, ui_manager);
	IwResManagerInit();
	IwGetResManager()->SetMode(CIwResManager::MODE_BUILD);
	IwGetResManager()->LoadGroup("main.group");

	resources = IwGetResManager()->GetGroupNamed("main");

	artist->set_resources(*resources);
}

Game::~Game(){
	IwGetResManager()->DestroyGroup("main");
	delete artist;
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
	artist->render(++timesteps);
}

Artist* Game::getArtist(){ return artist; }
