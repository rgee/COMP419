#include "statemanager.h"

void StateManager::tick(){

}

GameState* StateManager::peek_state() const{
	return states.back();
}

GameState* StateManager::pop_state(){
	if(!states.empty()) {
		return states.pop_back_get();
	} else {
		return NULL;
	}
}

void StateManager::push_state(GameState& newState){
	states.push_back(&newState);
}