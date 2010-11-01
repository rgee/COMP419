#include "dummyunit.h"

DummyUnit::DummyUnit(int _r, int _theta) : Unit(_r, _theta) {

	frames.push_back(Iw2DCreateImage("images/pacman-01.bmp"));
	frames.push_back(Iw2DCreateImage("images/pacman-02.bmp"));
	frames.push_back(Iw2DCreateImage("images/pacman-03.bmp"));

}

void DummyUnit::display(int centerX, int centerY, iwangle rotAngle, int frameNumber) {
	
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
		
	Iw2DDrawImage(frames[index], center);
}

DummyUnit::~DummyUnit() {

	for(CIwArray<CIw2DImage*>::iterator it = frames.begin(); it != frames.end(); ++it) {
		delete(*it);
	}
}