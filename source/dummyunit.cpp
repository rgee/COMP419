#include "dummyunit.h"

void DummyUnit::display(int centerX, int centerY, int rotAngle, int frameNumber) {
	
// Init with muncher stats for now. This is just a dummy.
DummyUnit::DummyUnit(Player* owner, Game* game, CIwVec2 position)
	: Unit(100.0f, 50.0f, 10.0f, 15.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game, position)
{
	texture_name = "pacman-01";

    frameNumber = 0;
	//frames.push_back(Iw2DCreateImage("images/pacman-01.bmp"));
	//frames.push_back(Iw2DCreateImage("images/pacman-02.bmp"));
	//frames.push_back(Iw2DCreateImage("images/pacman-03.bmp"));
}

void DummyUnit::display() {
//	CIwSVec2 center = CIwSVec2(centerX, centerY);
	Iw2DSetColour(0xff0ff0ff);

	Iw2DDrawImage(frames[(frameNumber/10) % 3], position);
}


DummyUnit::~DummyUnit() {

}
	for(CIwArray<CIw2DImage*>::iterator it = frames.begin(); it != frames.end(); ++it) {
		delete(*it);
	}
}

bool DummyUnit::update(){++frameNumber; return true;}

