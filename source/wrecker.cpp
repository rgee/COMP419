#include "wrecker.h"

Wrecker::Wrecker(Player* owner, Game* game, CIwFVec2 position)
	: Unit(350.0f, 100.0f, 40.0f, 5.0f, 5.0f, 5.0f, 40.0f, 0.0f, 0.0f, owner, game, position)
{
	spriteSize = 256;
	numFrames = 5;
	curFrame = 0;
    scale = 0.2;
}

bool Wrecker::update(){
    curFrame = (curFrame + 1) % numFrames;
    
    game->getAI()->updateAI(this);
	return true;
}

const char* Wrecker::getTextureName(){
    return "wrecker_walk_sprite_sheet";
}