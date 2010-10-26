#include "game.h"
#include "unit.h"
#include "gridcell.h"

void Game::addUnit(Unit *u){
    u->id = units->size();
    units->push_back(u);
}


GridCell * Game::getCell(int row, int col){
    return cells[row][col];
}

CIwArray<Unit*> Game::getUnitsNear(int row, int col, int radius){
    CIwArray<Unit*> units = new CIwArray();
    for (int r = row-radius; r <= row+radius; r++) {
        for (int c = col-radius; c <= col+radius; c++) {
            if (r >= 0 && r <= rows && c >= 0 && c <= cols) {
                units.push_back(getCell(r, c)->getUnits());
            }
        }
    }
    
    return units;
}