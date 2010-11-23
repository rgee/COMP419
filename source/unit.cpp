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
		Game* game, CIwFVec2 position)
		: hp(hp), cost(cost), attack(attack), speed(speed),
		  munch_speed(munch_speed), range(range), sight(sight),
		  spread_speed(spread_speed), spread_radius(spread_radius),
		  owner(owner), game(game), position(position),
		  theta(0.0f)
{
}
/*
Unit::Unit(float _r, float _theta) : r(r), theta(theta) {}
*/


void Unit::renderSprite(int frameNumber, float angle, float scaleFactor, float worldRot) {
	renderImageWorldSpace(position, angle, scaleFactor, spriteSize, worldRot, frameNumber, numFrames);
}


int Unit::getId(){ return uid; }
void Unit::setId(int uid){ this->uid = uid; }


Player& Unit::getOwner(){
	return *owner;
}

Game* Unit::getGame(){
	return game;
}

Unit* Unit::getAttacking(){return Attacking;}
void Unit::setAttacking(Unit* unit){Attacking = unit;}

Unit* Unit::getPursuing(){return Pursuing;}
void Unit::setPursuing(Unit* unit){Pursuing=unit;}

bool Unit::attacking(){
    return Attacking != NULL;
}

bool Unit::pursuing(){
    return Pursuing != NULL;
}


void Unit::setOwner(Player& p){
	owner = &p;
}

float Unit::getHp(){
	return hp;
}
float Unit::getRange(){return range;}

void Unit::setHp(float f){
	hp = f;
}

void Unit::decrementHp(float f){
	hp -= f;
}

void Unit::setPosition(float x, float y){
	position.x = x;
	position.y = y;
    
	r = position.GetLength();
	theta = asin(y/r);
}

void Unit::setPosition(const CIwFVec2& newPosition){
    setPosition(newPosition.x, newPosition.y);
}


CIwFVec2 Unit::getPosition(){ return position; }

float Unit::getR(){     return r; }
float Unit::getTheta(){ return theta; }

void Unit::setPolarPosition(float _r, float _theta){
    r = _r;
    theta = _theta;
    position.x = r * cos(theta);
    position.y = r * sin(theta);
}

void Unit::increaseX(float x){}
void Unit::increaseY(float y){}

float Unit::getX(){return position.x;}
float Unit::getY(){return position.y;}


float Unit::getSpeed(){return speed;}
float Unit::getSize(){return spriteSize/2;}

void Unit::Attack(){};
void Unit::RecieveDamage(){};


void Unit::setVelocity(const CIwFVec2& vel){
    velocity = vel;
}

void Unit::setVelocity(float xv, float yv){
    velocity.x = xv;
    velocity.y = yv;
}

CIwFVec2 Unit::getVelocity(){return velocity;}


float Unit::getSight(){ return sight; }

float Unit::getAngle(){
    // Facing towards position.x + velocity.x, position.y + velocity.y
    // 0 is facing LEFT
    // PI is facing RIGHT
    // Let phi be angle from X axis to (velocity.x, velocity.y)
    // So we want atan2(velocity.x, velocity.y)
    
    return 3*PI/2 - atan2(velocity.x, velocity.y);
}
