#include "thrower.h"

Thrower::Thrower(Player* owner, Game* game, float x, float y)
	: Unit(200.0f, 300.0f, 0.0f, 8.0f, 20.0f, 60.0f, 80.0f, 0.0f, 0.0f, owner, game)
{
    spriteSize = 256;
    numFrames = 8;
    curFrame = 0;
    scale = 0.5f;
    setPosition(x, y);

    
    statAttacks.insert(std::pair<unit_type, int>(MUNCHER,10));
    statAttacks.insert(std::pair<unit_type, int>(WRECKER,10));
    statAttacks.insert(std::pair<unit_type, int>(THROWER,10));
    statAttacks.insert(std::pair<unit_type, int>(SHOOTER,10));
    statAttacks.insert(std::pair<unit_type, int>(SPREADER,10));
    statAttacks.insert(std::pair<unit_type, int>(LEADER,10));

    framesUntilUpdate = 0;

}

Thrower::Thrower(const Thrower& newThrower) : Unit(newThrower) { }

bool Thrower::update(){   
    curFrame = (curFrame + 1) % numFrames;


    if(curFrame >= 4)
        game->getAI()->updateAI(this);
    
	return true;
}

unit_type Thrower::getType() {
	return THROWER;
}

Unit* Thrower::spawnCopy() {
    return new Thrower(*this);
} 

void Thrower::attack(){
    Unit* attacking = this->attackTarget;
    if((attacking->getPosition()-position).GetLength()>range){
        pursueTarget = attacking;
        attackTarget = NULL;
    }
    else{
        int dmg = getDammage(attacking);
        attacking->receiveDamage(dmg, this);
    }
}
void Thrower::receiveDamage(float amount, Unit* attacker){
    if (hp<=amount) {
        attacker->setAttacking(NULL);
        deathflag=true;
    } 
    else {
        hp = hp - amount;}
}

int Thrower::getDammage(Unit* unit){
    unit_type type = unit->getType();
    return statAttacks[type];

}


const char* Thrower::getTextureName(){
    return "thrower_walk_sprite_sheet";
}
