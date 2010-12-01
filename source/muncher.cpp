#include "muncher.h"

Muncher::Muncher(Player* owner, Game* game, float x, float y)
		 : Unit(100.0f, 50.0f, 10.0f, 25.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 12;
	curFrame = 0;
    scale = 0.2f;
    setPosition(x, y);
    //statAttacks = {{"Muncher",0},{"Wrecker",10},{"Thrower",0},{"Shooter",0},{"Invader",0},{"Spreader",0},{"Leader",0}};
}

Muncher::Muncher(const Muncher& newMuncher) : Unit(newMuncher) { }

bool Muncher::update() {
	
    curFrame = (curFrame + 1) % numFrames;
   
    if(curFrame == 0) {
		game->getAI()->updateAI(this);
	}
	
    
	return true;
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
