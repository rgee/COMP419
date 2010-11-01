#ifndef _GRIDCELL_H
#define _GRIDCELL_H

#include "IwArray.h"

class GridCell;

#include "unit.h"

class GridCell {
    private:
        Player *owner;
        CIwArray<Unit*> units;
        int row, col;
    
    public:
		GridCell();
		~GridCell(){}

        Player *getOwner();
        void setOwner(Player *p);

		void setCoords(int x, int y);
        
        void addUnit(Unit& u);
        bool hasUnit(Unit& u);
        CIwArray<Unit*> getUnits();
        void removeUnit(Unit& u);
};

#endif
