#ifndef DUMMY_UNIT_H
#define DUMMY_UNIT_H

#include "unit.h"
#include "IwUtil.h"

class DummyUnit : public Unit {
	
	public:
	
		DummyUnit(int _r, int _theta);
		~DummyUnit();
		void display(int centerX, int centerY, iwangle rotAngle, int frameNumber);
	
};

#endif