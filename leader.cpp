#include "leader.h"

Leader::Leader(Player* owner, Game* game, CIwFVec2 position)
	: Unit(1000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 550.0f, 15.0f, 400.0f, owner, game, position)
{

}

void Leader::display(){

}

bool Leader::update(){
	return true;
}