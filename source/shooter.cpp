#include "shooter.h"

Shooter::Shooter(Player* owner, Game* game, float x, float y)
	: Unit(200.0f, 250.0f, 50.0f, 0.0f, 15.0f, 50.0f, 100.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 7;
	curFrame = 0;
    scale = 0.35;
    setPosition(x, y);

	texture_names.push_back(IwHashString("shooter_sprite_sheet"));
}

Shooter::Shooter(const Shooter& newShooter) : Unit(newShooter) { }

bool Shooter::shouldAIUpdate() {
    return curFrame == 0;
}

bool Shooter::update(std::list<Unit*>::iterator itr){
    curFrame = (curFrame + 1) % numFrames;
    
    if(target == NULL){
        curFrame = 0;
    }
    
    return true;
}

unit_type Shooter::getType() {
	return SHOOTER;
}

Unit* Shooter::spawnCopy() {
	return new Shooter(*this);
}

void Shooter::attack(){
    if((target->getPosition()-position).GetLength() <= range){
        target->receiveDamage(getDamage(target), this);
    }
}


int Shooter::getDamage(Unit* unit){
    unit_type type = unit->getType();
    return statAttacks[type];
}

