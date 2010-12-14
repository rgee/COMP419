#include "thrower.h"

Thrower::Thrower(Player* owner, Game* game, CIwFVec2 position)
	: Unit(200.0f, 300.0f, 0.0f, 6.0f, 20.0f, 60.0f, 80.0f, 0.0f, 0.0f, owner, game, position)
{

}

void Thrower::display(){

}

bool Thrower::update(){
	return true;
}