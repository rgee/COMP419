#include "unit.h"

Unit::Unit(float _r, float _theta) {
	r = _r;
	theta = _theta;
}

float Unit::getR() {
	return r;
}

float Unit::getTheta() {
	return theta;
}

int getId() { return 0; }

void setId(int uid) {}

Player *getOwner() { return NULL; }

void setOwner(Player *p) {}

float getHp() { return 0.0; }

void setHp(float f) {}

void decrementHp(float f) {}
