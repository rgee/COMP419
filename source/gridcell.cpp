#include "gridcell.h"

GridCell::GridCell() {}

void GridCell::addUnit(Unit* unit) {
	units.insert(unit);
}


const set<Unit*>& GridCell::getUnits() const {
	return units;
}