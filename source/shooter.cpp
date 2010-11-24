#include "shooter.h"

Shooter::Shooter(Player* owner, Game* game, CIwFVec2 position)
	: Unit(200.0f, 250.0f, 50.0f, 0.0f, 15.0f, 50.0f, 100.0f, 0.0f, 0.0f, owner, game, position)
{
	spriteSize = 256;
	numFrames = 7;
	curFrame = 0;	
}

void Shooter::display() {
	renderSprite(curFrame+=2, 90, 0.7, game->getRotation());
}

bool Shooter::update(){
	
	game->getAI()->updateAI(this);
	return true;
}

char* Shooter::getTextureName() {
	return "shooter_sprite_sheet";
}
