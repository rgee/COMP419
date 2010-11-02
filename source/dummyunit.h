#ifndef DUMMY_UNIT_H
#define DUMMY_UNIT_H

#include "unit.h"
#include "IwUtil.h"

class DummyUnit : public Unit {
    
    private:
        int frameNumber;
        CIwArray<CIw2DImage*> frames;
	
	public:
	
		DummyUnit(Player* owner, Game* game, CIwVec2 position);
		~DummyUnit();

		// These were shadowing the virtual display call. Be sure to add virtual
		// to the declaration.
		//void display(int centerX, int centerY, iwangle rotAngle, int frameNumber);
        //bool update();

		virtual void display();
		virtual bool update();
};


#endif
