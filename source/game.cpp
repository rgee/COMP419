#include "game.h"

void Game::addUnit(Unit *u){
    u->setId(units.size());
    units.push_back(u);
}

GridCell * Game::getCell(int row, int col){
    return &(cells[row][col]);
}

/* This should translate fp coordinates to the nearest cell.
 * This function is incomplete.
 */
GridCell * Game::getCell(float r, float c){
	return getCell((int)(getHeight()*r), (int)(getWidth()*c));
}


CIwArray<Unit*>* Game::getUnitsNear(int row, int col, int radius){
    
	CIwArray<Unit*> *units = new CIwArray<Unit*>();
    for (int r = row-radius; r <= row+radius; r++) {
        for (int c = col-radius; c <= col+radius; c++) {
            if (r >= 0 && r <= rows && c >= 0 && c <= cols) {
				
				set<Unit*> cellUnits = getCell(r, c)->getUnits();
				for (set<Unit*>::iterator it = cellUnits.begin(); it != cellUnits.end(); ++it) {
					units->push_back(*it);
				}
            }
        }
    }
    
    return units;
}

void Game::tick(){
	CIwArray<GridCell*> *changes = new CIwArray<GridCell*>();
	//for(Unit * u = units.begin(); *u <= units.end(); u++){
		
	//}
}