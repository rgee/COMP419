#ifndef _GRIDCELL_H
#define _GRIDCELL_H

#include <set>
using namespace std;

class GridCell;

#include "unit.h"
#include "player.h"

class GridCell{
    private:
        Player *owner;
        set<Unit> units;
        int row, col;
    
    public:
        Player *getOwner();
        void    setOwner(Player *p);
        
        void addUnit(Unit *u);
        bool hasUnit(Unit *u);
        set<Unit*> getUnits();
        void removeUnit(Unit *u);
};

#endif