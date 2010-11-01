#ifndef _GRIDCELL_H
#define _GRIDCELL_H

#include <set>
using namespace std;

#include "unit.h"
#include "player.h"

class GridCell{
    private:
        //Player *owner;
        set<Unit*> units;
        float r, theta;
    
    public:
		
		GridCell();
        Player *getOwner();
        void    setOwner(Player *p);
		int getR();
		int getTheta();	
        void addUnit(Unit *u);
        bool hasUnit(Unit *u);
        const set<Unit*>& getUnits() const;
        void removeUnit(Unit *u);
};

#endif