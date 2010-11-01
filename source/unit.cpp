#include "unit.h"

Unit::Unit(float hp, float cost, float attack, float speed, 
		float munch_speed, float range, float sight,
		float spread_speed, float spread_radius, Player* owner,
		Game* game, CIwVec2 position)
		: hp(hp), cost(cost), attack(attack), speed(speed),
		  munch_speed(munch_speed), range(range), sight(sight),
		  spread_speed(spread_speed), spread_radius(spread_radius),
		  owner(owner), game(game), position(position)
{

}

int Unit::getId(){
	return uuid;
}

void Unit::setId(int uuid){
	this->uuid = uuid;
}

Player& Unit::getOwner(){
	return *owner;
}

void Unit::setOwner(Player& p){
	owner = &p;
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

void Unit::setPosition(int x, int y){
	position.x = x;
	position.y = y;
}

void Unit::setPosition(const CIwVec2& newPosition){
	position = newPosition;
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
