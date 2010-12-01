#include "wrecker.h"

Wrecker::Wrecker(Player* owner, Game* game, float x, float y)
	: Unit(350.0f, 100.0f, 40.0f, 5.0f, 5.0f, 5.0f, 40.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 5;
	curFrame = 0;
    scale = 0.2;
    setPosition(x, y);
    
    statAttacks.insert(std::pair<unit_type, int>(MUNCHER,10));
    statAttacks.insert(std::pair<unit_type, int>(WRECKER,10));
    statAttacks.insert(std::pair<unit_type, int>(THROWER,10));
    statAttacks.insert(std::pair<unit_type, int>(SHOOTER,0));
    statAttacks.insert(std::pair<unit_type, int>(SPREADER,0));
    statAttacks.insert(std::pair<unit_type, int>(LEADER,0));
}

Wrecker::Wrecker(const Wrecker& newWrecker) : Unit(newWrecker) { }

bool Wrecker::update(){
    curFrame = (curFrame + 1) % numFrames;
    
    game->getAI()->updateAI(this);
    
    return true;
}

const char* Wrecker::getTextureName(){
    return "wrecker_walk_sprite_sheet";
}

unit_type Wrecker::getType() {
	return WRECKER;
}

Unit* Wrecker::spawnCopy() {
	return new Wrecker(*this);
}
void Wrecker::attack(){
    Unit* attacking = this->attackTarget;
    int dmg = getDammage(attacking);
    attacking->receiveDamage(dmg, this);
}
void Wrecker::receiveDamage(float amount, Unit* attacker){
    if (hp<=amount) {
        attacker->setAttacking(NULL);
        //run death animation if we have any on this
        delete this;
    } 
    else {
        hp = hp - amount;}
}

int Wrecker::getDammage(Unit* unit){
    unit_type type = unit->getType();
    return statAttacks[type];
}
