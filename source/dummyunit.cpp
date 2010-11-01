#include "dummyunit.h"

void DummyUnit::display(int centerX, int centerY, iwangle rotAngle, int frameNumber) {
	
	CIwSVec2 center = CIwSVec2(centerX, centerY);
	CIwSVec2 size = CIwSVec2(7, 7);
	Iw2DSetColour(0xff0ff0ff);
	Iw2DFillArc(center, size, 0, 2*0x800);
}