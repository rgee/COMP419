#include "thrower.h"

Thrower::Thrower(Player* owner, Game* game, float x, float y)
	: Unit(200.0f, 300.0f, 0.0f, 8.0f, 20.0f, 60.0f, 80.0f, 0.0f, 0.0f, owner, game)
{
    spriteSize = 256;
    numFrames = 8;
    curFrame = 0;
    scale = 0.5f;
    setPosition(x, y);

	texture_names.push_back(IwHashString("thrower_walk_sprite_sheet"));
    
    statAttacks.insert(std::pair<unit_type, int>(MUNCHER,10));
    statAttacks.insert(std::pair<unit_type, int>(WRECKER,10));
    statAttacks.insert(std::pair<unit_type, int>(THROWER,10));
    statAttacks.insert(std::pair<unit_type, int>(SHOOTER,10));
    statAttacks.insert(std::pair<unit_type, int>(SPREADER,10));
    statAttacks.insert(std::pair<unit_type, int>(LEADER,10));

    framesUntilUpdate = 0;

}

Thrower::Thrower(const Thrower& newThrower) : Unit(newThrower) { }

bool Thrower::shouldAIUpdate() {
    return curFrame >= 4;
}

bool Thrower::update(){   
    curFrame = (curFrame + 1) % numFrames;
    
	return true;
}

unit_type Thrower::getType() {
	return THROWER;
}

Unit* Thrower::spawnCopy() {
    return new Thrower(*this);
} 

void Thrower::attack(){
    if((target->getPosition()-position).GetLength() <= range){
        target->receiveDamage(getDamage(target), this);
    }
}


int Thrower::getDamage(Unit* unit){
    unit_type type = unit->getType();
    return statAttacks[type];

}
