#include "unit.h"

Unit::Unit(const Unit& newUnit)
	: hp(newUnit.hp), cost(newUnit.cost), attack(newUnit.attack), speed(newUnit.speed),
	munch_speed(newUnit.munch_speed), range(newUnit.range), sight(newUnit.sight),
	spread_speed(newUnit.spread_speed), spread_radius(newUnit.spread_radius),
	owner(newUnit.owner), game(newUnit.game), position(newUnit.position)
{

}


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

void Unit::renderSprite(int frameNumber, float angle, float scaleFactor) {
	
	renderImageWorldSpace(position, angle, scaleFactor, spriteSize, frameNumber, numFrames);
}

int Unit::getId(){ return uid; }

void Unit::setId(int uid){ this->uid = uid; }

void Unit::setR(float x){ r = x; }

void Unit::setTheta(float y){ theta = y; }

Player& Unit::getOwner(){ return *owner; }

void Unit::setOwner(Player& p){ owner = &p;}

float Unit::getHp(){ return hp; }

void Unit::setHp(float f){ hp = f; }

Player *getOwner() { return 0; }

void Unit::decrementHp(float f){ hp -= f; }

void Unit::setPosition(int x, int y){
	position.x = x;
	position.y = y;
}

void Unit::setPosition(const CIwVec2& newPosition){
	position = newPosition;
}


float Unit::getR(){ return r; }

float Unit::getTheta(){ return theta; }

void Unit::increaseX(float x){}

void Unit::increaseY(float y){}

float Unit::getX(){return 0.0f;}

float Unit::getY(){return 0.0f;}

void Unit::setVelocity(const CIwSVec2& vel)
{
    float angle = acos(vel.Dot(velocity));

    velocity = vel;
}
