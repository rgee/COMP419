#include "game.h"

int Unit::getId(){
	return uuid;
}

void Unit::setId(int uuid){
	this->uuid = uuid;
}

Player *Unit::getOwner(){
	return owner;
}

void Unit::setOwner(Player *p){
	owner = p;
}

float Unit::getHp(){
	return hp;
}

void Unit::setHp(float f){
	hp = f;
}

void Unit::decrementHp(float f){
	hp -= f;
}

void Unit::setRow(float x){
	row = x;
}

float Unit::getRow(){
	return row;
}

void Unit::setCol(float y){
	col = y;
}

float Unit::getCol(){
	return col;
}

void Unit::increaseX(float x){}
void Unit::increaseY(float y){}
float Unit::getX(){return 0.0f;}
float Unit::getY(){return 0.0f;}