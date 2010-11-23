#include "wrecker.h"

Wrecker::Wrecker(Player* owner, Game* game, CIwFVec2 position)
	: Unit(350.0f, 100.0f, 40.0f, 10.0f, 5.0f, 5.0f, 40.0f, 0.0f, 0.0f, owner, game, position)
{

}

void Wrecker::display(){

}

bool Wrecker::update(){
	return true;
}