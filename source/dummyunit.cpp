#include "dummyunit.h"


// Init with muncher stats for now. This is just a dummy.
DummyUnit::DummyUnit(Player* owner, Game* game, CIwVec2 position)
	: Unit(100.0f, 50.0f, 10.0f, 15.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game, position)
{
	frames.push_back(Iw2DCreateImage("images/pacman-01.bmp"));
	frames.push_back(Iw2DCreateImage("images/pacman-02.bmp"));
	frames.push_back(Iw2DCreateImage("images/pacman-03.bmp"));
}

void DummyUnit::display() {
	/*
	CIwSVec2 center = CIwSVec2(centerX, centerY);
	Iw2DSetColour(0xff0ff0ff);
		
	int index;
	
	if(frameNumber < 10) {
		index = 0;
	}
	else if(frameNumber < 20) {
		index = 1;
	}
	else {
		index = 2;
	}
	*/

	Iw2DDrawImage(frames[0], position);
}


DummyUnit::~DummyUnit() {

	for(CIwArray<CIw2DImage*>::iterator it = frames.begin(); it != frames.end(); ++it) {
		delete(*it);
	}
}

bool DummyUnit::update(){return true;}

