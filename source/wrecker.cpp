#include "wrecker.h"

Wrecker::Wrecker(Player* owner, Game* game, float x, float y)
	: Unit(350.0f, 100.0f, 40.0f, 5.0f, 5.0f, 5.0f, 40.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 6;
	curFrame = 0;
    scale = 0.2;
    setPosition(x, y);
    
    statAttacks.insert(std::pair<unit_type, int>(MUNCHER,10));
    statAttacks.insert(std::pair<unit_type, int>(WRECKER,10));
    statAttacks.insert(std::pair<unit_type, int>(THROWER,10));
    statAttacks.insert(std::pair<unit_type, int>(SHOOTER,10));
    statAttacks.insert(std::pair<unit_type, int>(SPREADER,10));
    statAttacks.insert(std::pair<unit_type, int>(LEADER,10));
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

void Wrecker::attack(){
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
void Wrecker::receiveDamage(float amount, Unit* attacker){
    if (hp<=amount) {
        attacker->setAttacking(NULL);
        deathflag = true;
    } 
    else {
        hp = hp - amount;}
}

int Wrecker::getDammage(Unit* unit){
    unit_type type = unit->getType();
    return statAttacks[type];
}

