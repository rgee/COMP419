#include "unit.h"

Unit::Unit(const Unit& newUnit)
	: WorldObject(newUnit.position, newUnit.game), 
	hp(newUnit.hp), cost(newUnit.cost), attack(newUnit.attack), speed(newUnit.speed),
	munch_speed(newUnit.munch_speed), range(newUnit.range), sight(newUnit.sight),
	spread_speed(newUnit.spread_speed), spread_radius(newUnit.spread_radius),
	owner(newUnit.owner)
{

}

Unit::Unit(float hp, float cost, float attack, float speed, 
		float munch_speed, float range, float sight,
		float spread_speed, float spread_radius, Player* owner,
		Game* game, CIwFVec2 position)
		: WorldObject(position, game),
		  hp(hp), cost(cost), attack(attack), speed(speed),
		  munch_speed(munch_speed), range(range), sight(sight),
		  spread_speed(spread_speed), spread_radius(spread_radius),
		  owner(owner)
{
	
}


void Unit::renderSprite(int frameNumber, float angle, float scaleFactor, float worldRot) {
	
	CIwColour ownerColor = owner->getColor();
	
	static CIwColour colors[4] = {
		ownerColor,
		ownerColor,
		ownerColor,
		ownerColor
	};
	
	IwGxSetColStream(colors, 4);
	
	renderImageWorldSpace(position, angle, scaleFactor, spriteSize, worldRot, frameNumber, numFrames);
}

void Unit::display(){
    renderImageWorldSpace(position, getAngle(), scale, spriteSize, game->getRotation(), curFrame, numFrames);
}

void Unit::displayOnScreen(int x, int y){    
    
	CIwMaterial *mat = new CIwMaterial();
    mat->SetTexture((CIwTexture*)game->getSprites()->GetResNamed(getTextureName(), IW_GX_RESTYPE_TEXTURE));
    mat->SetModulateMode(CIwMaterial::MODULATE_RGB);
    mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
    IwGxSetMaterial(mat);
    
	CIwSVec2 xy(x-30, y-30);
    CIwSVec2 duv(IW_FIXED(1.0/numFrames), IW_GEOM_ONE);
    
	static CIwSVec2 wh(60, 60);
	static CIwSVec2 uv(IW_FIXED(0), IW_FIXED(0));	
    
    IwGxSetScreenSpaceSlot(1);
    IwGxDrawRectScreenSpace(&xy, &wh, &uv, &duv);
    
    free(mat);
}


int Unit::getId(){ return uid; }
void Unit::setId(int uid){ this->uid = uid; }

bool Unit::operator<(const Unit& u) const{
	return theta < u.theta;
}


Player& Unit::getOwner(){
	return *owner;
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


void Unit::setOwner(Player* p){
	owner = p;
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

void Unit::increaseX(float x){}
void Unit::increaseY(float y){}


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
