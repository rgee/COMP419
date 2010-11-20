#include "shooter.h"

Shooter::Shooter(Player* owner, Game* game, CIwVec2 position)
	: Unit(200.0f, 250.0f, 50.0f, 0.0f, 15.0f, 50.0f, 100.0f, 0.0f, 0.0f, owner, game, position)
{

}

void Shooter::display(){

}

bool Shooter::update(){
	return true;
}