#include "muncher.h"

Muncher::Muncher(Player* owner, Game* game, float x, float y)
		 : Unit(100.0f, 50.0f, 10.0f, 25.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 12;
	curFrame = 0;
    scale = 0.2f;
    setPosition(x, y);
    statAttacks.insert(std::pair<unit_type, int>(MUNCHER,0));
    statAttacks.insert(std::pair<unit_type, int>(WRECKER,10));
    statAttacks.insert(std::pair<unit_type, int>(THROWER,0));
    statAttacks.insert(std::pair<unit_type, int>(SHOOTER,0));
    statAttacks.insert(std::pair<unit_type, int>(SPREADER,0));
    statAttacks.insert(std::pair<unit_type, int>(LEADER,0));
}

Muncher::Muncher(const Muncher& newMuncher) : Unit(newMuncher) { }

bool Muncher::update() {
	
    curFrame = (curFrame + 1) % numFrames;
   
    if(curFrame == 0) {
		game->addIcing(new Icing(position, game, owner));
		game->getAI()->updateAI(this);
	}
    
	return true;
}
void Muncher::attack(){
    Unit* attacking = this->attackTarget;
    int dmg = getDammage(attacking);
    attacking->receiveDamage(dmg, this);
}
void Muncher::receiveDamage(float amount, Unit* attacker){
    if (hp<=amount) {
        attacker->setAttacking(NULL);
        //run death animation if we have any on this
        delete this;
    } 
    else {
        hp = hp - amount;}
}

int Muncher::getDammage(Unit* unit){
    unit_type type = unit->getType();
    return statAttacks[type];
}

const char* Muncher::getTextureName() {
	return "muncher_sprite_sheet";
}

Unit* Muncher::spawnCopy() {
	return new Muncher(*this);
}

unit_type Muncher::getType() {
	return MUNCHER;
}
