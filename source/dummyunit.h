#ifndef DUMMY_UNIT_H
#define DUMMY_UNIT_H

#include "unit.h"

class DummyUnit : public Unit {
	
	public:
	
		DummyUnit(int _r, int _theta) : Unit(_r, _theta) {}
		void display(int centerX, int centerY, iwangle rotAngle, int frameNumber);
};

#endif