#include "thrower.h"

Thrower::Thrower(Player* owner, Game* game, float x, float y)
	: Unit(200.0f, 300.0f, 0.0f, 6.0f, 20.0f, 60.0f, 80.0f, 0.0f, 0.0f, owner, game)
{
    spriteSize = 256;
    numFrames = 8;
    curFrame = 0;
    scale = 0.25f;
    setPosition(x, y);
}

Thrower::Thrower(const Thrower& newThrower) : Unit(newThrower) { }

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


const char* Thrower::getTextureName(){
    return "thrower_walk_sprite_sheet";
}