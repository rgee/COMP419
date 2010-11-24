#include "shooter.h"

Shooter::Shooter(Player* owner, Game* game, CIwFVec2 position)
	: Unit(200.0f, 250.0f, 50.0f, 0.0f, 15.0f, 50.0f, 100.0f, 0.0f, 0.0f, owner, game, position)
{
	spriteSize = 256;
	numFrames = 7;
	curFrame = 0;	
}

void Shooter::display() {
    curFrame = (curFrame + 2);// % numFrames;
	renderSprite(curFrame, 90, 0.5, game->getRotation());
}

bool Shooter::update(){
	
	game->getAI()->updateAI(this);
	return true;
}

const char* Shooter::getTextureName() {
	return "shooter_sprite_sheet";
}
