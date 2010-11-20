#include "unit.h"
#include "s3ePointer.h"

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
/*
Unit::Unit(float _r, float _theta) : r(r), theta(theta) {}
*/


void Unit::renderSprite(int frameNumber, float angle, float scaleFactor) {
		
	int left = position.x;
	int top = position.y;	
	
	static CIwSVec3 vertices[4];
	static CIwSVec2 UVs[4];
	
	//set up model space vertices
	
	int vertexDist = scaleFactor*spriteSize/2;
	
	vertices[0] = CIwSVec3(-1*vertexDist, -1*vertexDist, -1);
	vertices[2] = CIwSVec3(vertexDist, -1*vertexDist, -1);
	vertices[3] = CIwSVec3(vertexDist, vertexDist, -1);
	vertices[1] = CIwSVec3(-1*vertexDist, vertexDist, -1);
	
	CIwMat modelTransform = CIwMat::g_Identity;
	modelTransform.SetRotZ(TO_RADIANS(angle));
	modelTransform.SetTrans(CIwVec3(left, -1*top, 1));
	IwGxSetModelMatrix(&modelTransform, false);
	
	int squaredSize = spriteSize*spriteSize;
	int offset = squaredSize/numFrames;
	
	//set up sprite UV's
	UVs[0] = CIwSVec2(frameNumber*offset, 0);
	UVs[2] = CIwSVec2((frameNumber+1)*offset, 0);
	UVs[3] = CIwSVec2((frameNumber+1)*offset, squaredSize);
	UVs[1] = CIwSVec2(frameNumber*offset, squaredSize);

	//render the unit in model space
	IwGxSetUVStream(UVs);
	IwGxSetColStream(NULL);
	IwGxSetVertStreamModelSpace(vertices, 4);
	IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);
	IwGxFlush();
}


int Unit::getId(){ return uid; }
void Unit::setId(int uid){ this->uid = uid; }



void Unit::setRTheta(float rad, float ang){ 
	r = rad;
	theta = ang;
	position.x = (r/sin(theta))-1;
	position.y = position.x*sin(theta);
}

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

bool Unit::attacking(){if(Attacking!=NULL){return true;}else{return false;}}
bool Unit::pursuing(){if(Pursuing!=NULL){return true;}else{return false;}}



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

void Unit::setPosition(int x, int y){
	position.x = x;
	position.y = y;
	r = sqrt(x^2 + y^2);
	theta = asin(y/x);
	
}

void Unit::setPosition(const CIwVec2& newPosition){
	position = newPosition;
	float x = newPosition.x;
	float y = newPosition.y;
	r = sqrt(x*x + y*y);
	theta = asin(y/x);
}


CIwSVec2 Unit::getPosition(){return position;}

float Unit::getR(){ return r; }
float Unit::getTheta(){ return theta; }

void Unit::increaseX(float x){}
void Unit::increaseY(float y){}
float Unit::getX(){return 0.0f;}
float Unit::getY(){return 0.0f;}


float Unit::getSpeed(){return speed;}

void Unit::Attack(){};
void Unit::RecieveDamage(){};


void Unit::setVelocity(const CIwSVec2& vel)
{
    float angle = acos(vel.Dot(velocity));


    velocity = vel;
}
