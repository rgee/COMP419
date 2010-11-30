#include "thrower.h"

Thrower::Thrower(Player* owner, Game* game, float x, float y)
	: Unit(200.0f, 300.0f, 0.0f, 6.0f, 20.0f, 60.0f, 80.0f, 0.0f, 0.0f, owner, game)
{
    setPosition(x, y);
}

Thrower::Thrower(const Thrower& newThrower) : Unit(newThrower) { }

void Thrower::display(){

}

bool Thrower::update(){
	return true;
}

unit_type Thrower::getType() {
	return THROWER;
}

Unit* Thrower::spawnCopy() {
    return NULL;
	//return new Thrower(*this);
}