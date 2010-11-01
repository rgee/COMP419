#include "game.h"
#include "unit.h"
#include "gridcell.h"

void Game::addUnit(Unit *u){
    u->setId(units.size());
    units.push_back(u);
}

GridCell * Game::getCell(int row, int col){
    return &(cells[row][col]);
}

CIwArray<Unit*>* Game::getUnitsNear(int row, int col, int radius){
    
	CIwArray<Unit*>* unitsNear = new CIwArray<Unit*>();
    for (int r = row-radius; r <= row+radius; r++) {
        for (int c = col-radius; c <= col+radius; c++) {
            if (r >= 0 && r <= rows && c >= 0 && c <= cols) {
				
				set<Unit*> cellUnits = getCell(r, c)->getUnits();
				for (set<Unit*>::iterator it = cellUnits.begin(); it != cellUnits.end(); ++it) {
					unitsNear->push_back(*it);
				}
            }
        }
    }
    
    return unitsNear;
}