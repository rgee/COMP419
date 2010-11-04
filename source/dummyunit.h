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
		void display(int centerX, int centerY, iwangle rotAngle, int frameNumber);

		virtual void display();
		virtual bool update();
};


#endif
