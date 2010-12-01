#include "wrecker.h"

Wrecker::Wrecker(Player* owner, Game* game, float x, float y)
	: Unit(350.0f, 100.0f, 40.0f, 5.0f, 5.0f, 5.0f, 40.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 6;
	curFrame = 0;
    scale = 0.2;
    setPosition(x, y);
}

Wrecker::Wrecker(const Wrecker& newWrecker) : Unit(newWrecker) { }

bool Wrecker::update(){
    curFrame = (curFrame + 1) % numFrames;
    
    game->getAI()->updateAI(this);
    
    return true;
}

const char* Wrecker::getTextureName(){
    if (attackTarget == NULL) {
        numFrames = 6;
        return "wrecker_walk_sprite_sheet";
    }else{
        numFrames = 8;
        return "wrecker_attack_sprite_sheet";
    }
}

unit_type Wrecker::getType() {
	return WRECKER;
}

Unit* Wrecker::spawnCopy() {
	return new Wrecker(*this);
}
