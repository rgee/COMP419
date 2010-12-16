#include "muncher.h"

Muncher::Muncher(Player* owner, Game* game, float x, float y)
		 : Unit(100.0f, 50.0f, 10.0f, 4.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 12;
	curFrame = 0;
    scale = 0.2f;
    setPosition(x, y);
    /*statAttacks.insert(std::pair<unit_type, int>(MUNCHER,0));
    statAttacks.insert(std::pair<unit_type, int>(WRECKER,10));
    statAttacks.insert(std::pair<unit_type, int>(THROWER,0));
    statAttacks.insert(std::pair<unit_type, int>(SHOOTER,0));
    statAttacks.insert(std::pair<unit_type, int>(SPREADER,0));
    statAttacks.insert(std::pair<unit_type, int>(LEADER,0));*/

	texture_names.push_back(IwHashString("muncher_sprite_sheet"));
}

Muncher::Muncher(const Muncher& newMuncher) : Unit(newMuncher) { }

bool Muncher::update(std::list<Unit*>::iterator itr) {
    curFrame = (curFrame + 1) % numFrames;   
	path(itr);
	return true;
}
void Muncher::attack(){
    if((target->getPosition()-position).GetLength() <= range){
        target->receiveDamage(getDamage(target), this);
    }
}

int Muncher::getDamage(Unit* unit){
    unit_type type = unit->getType();
    return statAttacks[type];
}

Unit* Muncher::spawnCopy() {
	s3eDebugOutputString("spawn copy");
	return new Muncher(*this);
}

unit_type Muncher::getType() {
	return MUNCHER;
}
