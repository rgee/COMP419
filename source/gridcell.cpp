#include "gridcell.h"

CIwArray<Unit*> GridCell::getUnits(){
	return units;
}

bool GridCell::hasUnit(Unit* u){
	return units.find(u) != -1 ? true : false;
}

void GridCell::addUnit(Unit* u){
	units.append(u);
}

void GridCell::removeUnit(Unit* u){
	units.find_and_remove_fast(u);
}

void GridCell::setCoords(int x, int y){
	row = x;
	col = y;
}

Player* GridCell::getOwner(){
	return owner;
}

void GridCell::setOwner(Player* p){
	owner = p;
}