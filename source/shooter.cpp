#include "shooter.h"

Shooter::Shooter(Player* owner, Game* game, float x, float y)
	: Unit(200.0f, 250.0f, 50.0f, 0.0f, 15.0f, 50.0f, 100.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 7;
	curFrame = 0;
    scale = 0.35;
    setPosition(x, y);
}

Shooter::Shooter(const Shooter& newShooter) : Unit(newShooter) { }

bool Shooter::update(){
    curFrame = (curFrame + 1) % numFrames;
    
    if(attackTarget == NULL){
        curFrame = 0;
    }
    
    if(curFrame == 0)
        game->getAI()->updateAI(this);
    
    return true;
}

const char* Shooter::getTextureName() {
	return "shooter_sprite_sheet";
}

unit_type Shooter::getType() {
	return SHOOTER;
}

Unit* Shooter::spawnCopy() {
	return new Shooter(*this);
}
