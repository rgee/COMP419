#include "gridcell.h"

GridCell::GridCell() {
	
	units = new set<Unit*>();
	DummyUnit *test = new DummyUnit(5.0, 100);
	units->insert(test);
}

GridCell::~GridCell(){
	delete units;
}

set<Unit*>* GridCell::getUnits() {
	return units;
}