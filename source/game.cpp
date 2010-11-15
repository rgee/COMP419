#include "game.h"
#include "unit.h"
#include "artist.h"

Game::Game(int numPlayers) : numPlayers(numPlayers) {
	ui_manager = new UIManager();
	IwResManagerInit();
	
}

Game::~Game(){
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
	render();
}

void Game::render() {
	
	for (CIwArray<Unit*>::iterator itr = units.begin(); itr != units.end(); ++itr) {
		
	}
}