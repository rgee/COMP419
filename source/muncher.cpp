#include "muncher.h"

Muncher::Muncher(Player* owner, Game* game, float x, float y)
		 : Unit(100.0f, 50.0f, 10.0f, 4.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 12;
	curFrame = 0;
    scale = 0.2f;
    setPosition(x, y);
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

Unit* Muncher::spawnCopy() {
	return new Muncher(*this);
}

unit_type Muncher::getType() {
	return MUNCHER;
}
