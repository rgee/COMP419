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


void Unit::renderSprite(int frameNumber, float angle) {

	int top = position.x;
	int left = position.y;
	
	CIwSVec2* vertices = (CIwSVec2*)malloc(sizeof(CIwSVec2)*4);
	CIwSVec2* UVs = (CIwSVec2*)malloc(sizeof(CIwSVec2)*4);
	
	vertices[0] = CIwSVec2(left, top);
	vertices[2] = CIwSVec2(left+spriteSize, top);
	vertices[3] = CIwSVec2(left+spriteSize, top+spriteSize);
	vertices[1] = CIwSVec2(left, top+spriteSize);
	
	//set up UV offset for the given frame number
	//TODO This was figured out purely by trial and error, and only works
	//for sheets with 64x64 sprites. Need to figure out how Airplay interprets
	//UV coordinates - makes no sense to me right now.

	UVs[0] = CIwSVec2(frameNumber*682, 0);
	UVs[2] = CIwSVec2((frameNumber+1)*682, 0);
	UVs[3] = CIwSVec2((frameNumber+1)*682, 4096);
	UVs[1] = CIwSVec2(frameNumber*682, 4096);
	
	//render the image to screen
	//TODO add support for rotation/scaling
	IwGxSetUVStream(UVs);
	IwGxSetColStream(NULL);
	IwGxSetVertStreamScreenSpace(vertices, 4);
	IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);
	
	IwGxFlush();
	
	free(vertices);
	free(UVs);
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
