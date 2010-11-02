#include "gridcell.h"

GridCell::GridCell() {}

const CIwArray<Unit*> GridCell::getUnits() const{
	return units;
}

bool GridCell::hasUnit(Unit* u){
	return false; //return units.find(u) != -1 ? true : false;
}

void GridCell::addUnit(Unit* u){
	units.push_back(u);
}

void GridCell::removeUnit(Unit* u){
	units.find_and_remove_fast(u);
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