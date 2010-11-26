#include "shooter.h"

Shooter::Shooter(Player* owner, Game* game, float x, float y)
	: Unit(200.0f, 250.0f, 50.0f, 0.0f, 15.0f, 50.0f, 100.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 7;
	curFrame = 0;
    scale = 0.3;
    setPosition(x, y);
}

bool Shooter::update(){
    curFrame = (curFrame + 1) % numFrames;
    
    if(curFrame == 0)
        game->getAI()->updateAI(this);
    
    return true;
}

const char* Shooter::getTextureName() {
	return "shooter_sprite_sheet";
}
