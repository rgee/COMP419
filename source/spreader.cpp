#include "spreader.h"

Spreader::Spreader(Player* owner, Game* game, CIwFVec2 position)
	: Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 300.0f, owner, game, position)
{
	spriteSize = 256;
	numFrames = 11;
	curFrame = 0;	
}

void Spreader::display(){
	renderSprite(curFrame, getAngle(), 0.2, game->getRotation());
}

bool Spreader::update(){
	curFrame = curFrame != numFrames ? curFrame + 1 : 0;
	return true;
}

const char* Spreader::getTextureName(){
    return "spreader_sprite_sheet";
}
