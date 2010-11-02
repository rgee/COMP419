#include "unit.h"

Unit::Unit(float _r, float _theta) : r(r), theta(theta) {}

int Unit::getId(){ return uid; }
void Unit::setId(int uid){ this->uid = uid; }

Player *Unit::getOwner(){ return owner; }
void Unit::setOwner(Player *p){ owner = p; }

float Unit::getHp(){ return hp; }
void Unit::setHp(float f){ hp = f; }
void Unit::decrementHp(float f){ hp -= f; }

void Unit::setR(float x){ r = x; }
void Unit::setTheta(float y){ theta = y; }

float Unit::getR(){ return r; }
float Unit::getTheta(){ return theta; }

void Unit::increaseX(float x){}
void Unit::increaseY(float y){}
float Unit::getX(){return 0.0f;}
float Unit::getY(){return 0.0f;}