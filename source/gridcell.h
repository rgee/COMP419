#ifndef _GRIDCELL_H
#define _GRIDCELL_H

#include <set>
#include "dummyunit.h"
using namespace std;

#include "unit.h"
#include "player.h"

class GridCell{
    private:
        Player *owner;
        set<Unit*>* units;
        float r, theta;
    
    public:
		
		GridCell();
		~GridCell();
        Player *getOwner();
        void    setOwner(Player *p);
		int getR();
		int getTheta();	
        void addUnit(Unit *u);
        bool hasUnit(Unit *u);
        set<Unit*>* getUnits();
        void removeUnit(Unit *u);
};

#endif