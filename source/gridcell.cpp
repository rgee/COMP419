#include "gridcell.h"

GridCell::GridCell() {}

const CIwArray<Unit*> GridCell::getUnits() const{
	return units;
}


// This takes a ref instead of a pointer because the search parameters
// should never be null.
bool GridCell::hasUnit(Unit& u){
	return units.find(&u) != -1 ? true : false;
}

void GridCell::addUnit(Unit& u){
	units.append(&u);
}

// This takes a ref instead of a pointer because the search parameters
// should never be null.
void GridCell::removeUnit(Unit& u){
	units.find_and_remove_fast(&u);
}

void GridCell::setCoords(int _r, int _theta){
	r = _r;
	theta = _theta;
}

Player* GridCell::getOwner(){
	return owner;
}

void GridCell::setOwner(Player* p){
	owner = p;
}
