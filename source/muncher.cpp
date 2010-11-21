#include "muncher.h"

Muncher::Muncher(Player* owner, Game* game, CIwFVec2 position)
		 : Unit(100.0f, 50.0f, 10.0f, 15.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game, position)
{
	spriteSize = 64;
	numFrames = 6;
	curFrame = 0;
	circleOffset = 0.0;
}

bool Muncher::update() {
	//a silly "pathing" calculation for testing purposes only
	curFrame = (curFrame < numFrames-1) ? curFrame+1 : 0;
	circleOffset += .3;
	return true;
}

void Muncher::display() {
	renderSprite(curFrame, 90, 1.0);
}

char* Muncher::getTextureName() {
	return "muncher_sprite_sheet";
}