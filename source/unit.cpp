#include "unit.h"

Unit::Unit(const Unit& newUnit)
	: WorldObject(newUnit), 
	hp(newUnit.hp), cost(newUnit.cost), attackDamage(newUnit.attackDamage), speed(newUnit.speed),
	munch_speed(newUnit.munch_speed), range(newUnit.range), sight(newUnit.sight),
	spread_speed(newUnit.spread_speed), spread_radius(newUnit.spread_radius),
	owner(newUnit.owner), scale(newUnit.scale), attackTarget(newUnit.attackTarget), 
	pursueTarget(newUnit.pursueTarget), curFrame(0), numFrames(newUnit.numFrames), 
	spriteSize(newUnit.spriteSize)
{

}

Unit::Unit(float hp, float cost, float attack, float speed, 
		float munch_speed, float range, float sight,
		float spread_speed, float spread_radius, Player* owner,
		Game* game)
		: WorldObject(game),
		  hp(hp), cost(cost), attackDamage(attack), speed(speed),
		  munch_speed(munch_speed), range(range), sight(sight),
		  spread_speed(spread_speed), spread_radius(spread_radius),
		  owner(owner), curFrame(0), attackTarget(NULL), pursueTarget(NULL)
{
	
}

void Unit::display(){
	IwGxSetColStream(owner->getColors(), 4);
    renderImageWorldSpace(position, getAngle(), scale, spriteSize, game->getRotation(), curFrame, numFrames, 0.0f);
    //if(pursuing()) {
    //    IwGxDebugPrimLine(CIwVec3(position.x, position.y, 1), CIwVec3(pursueTarget->getPosition().x, pursueTarget->getPosition().y, 1));
    //}

    /* UNCOMMENT TO DRAW DEBUG PRIMITIVES. Yellow circle = Unit Sight. Blue circle = Unit bounding volume
    CIwMat pMat = CIwMat::g_Identity;
    pMat.SetTrans(CIwVec3(position.x, -position.y, 1));

    IwGxDebugPrimCircle(pMat, sight, 2,IwGxGetColFixed(IW_GX_COLOUR_YELLOW), false);
    IwGxDebugPrimCircle(pMat, getSize(), 2,IwGxGetColFixed(IW_GX_COLOUR_BLUE), false);
    */
}

void Unit::displayOnScreen(int x, int y){    
    
	CIwMaterial *mat = new CIwMaterial();
    mat->SetTexture((CIwTexture*)game->getSprites()->GetResNamed(getTextureName(), IW_GX_RESTYPE_TEXTURE));
    mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
    mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
    IwGxSetMaterial(mat);
    
	CIwSVec2 xy(x-30, y-30);
    CIwSVec2 duv(IW_FIXED(1.0/numFrames), IW_GEOM_ONE);
    
	static CIwSVec2 wh(60, 60);
	static CIwSVec2 uv(IW_FIXED(0), IW_FIXED(0));	
    
    IwGxSetScreenSpaceSlot(1);
    IwGxDrawRectScreenSpace(&xy, &wh, &uv, &duv);
    
    delete mat;
}


int Unit::getId(){ return uid; }
void Unit::setId(int uid){ this->uid = uid; }

bool Unit::operator<(const Unit& u) const{
	return theta < u.theta;
}


Player& Unit::getOwner(){
	return *owner;
}

Unit* Unit::getAttacking(){ return attackTarget; }
void Unit::setAttacking(Unit* unit){ attackTarget = unit; }

Unit* Unit::getPursuing(){ return pursueTarget; }
void Unit::setPursuing(Unit* unit){ pursueTarget = unit; }

bool Unit::attacking(){
    return attackTarget != NULL;
}

bool Unit::pursuing(){
    return pursueTarget != NULL;
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

float Unit::getSpeed(){return speed;}
float Unit::getSize(){return 10.0f;}

void Unit::attack(){}

void Unit::receiveDamage(float amount, Unit *attacker){}

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
    CIwFVec2 norm = velocity.GetNormalised();
    return PI + atan2(norm.y, norm.x);
}

