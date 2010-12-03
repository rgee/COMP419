#include "unit.h"
#include "IwGeom.h"

Unit::Unit(const Unit& newUnit)
	: WorldObject(newUnit), 
	hp(newUnit.hp), cost(newUnit.cost), attackDamage(newUnit.attackDamage), speed(newUnit.speed),
	munch_speed(newUnit.munch_speed), range(newUnit.range), sight(newUnit.sight),
	spread_speed(newUnit.spread_speed), spread_radius(newUnit.spread_radius),
	scale(newUnit.scale), target(NULL), curFrame(0), numFrames(newUnit.numFrames), spriteSize(newUnit.spriteSize)
{
	setOwner(newUnit.owner);
}

Unit::Unit(float hp, float cost, float attack, float speed, 
		float munch_speed, float range, float sight,
		float spread_speed, float spread_radius, Player* owner,
		Game* game)
		: WorldObject(game),
		  hp(hp), cost(cost), attackDamage(attack), speed(speed),
		  munch_speed(munch_speed), range(range), sight(sight),
		  spread_speed(spread_speed), spread_radius(spread_radius),
		  curFrame(0), target(NULL)
{
    setOwner(owner);
}

bool Unit::isLocal(){
    return localPlayedOwnsThis;
}

void Unit::display(){
	IwGxSetColStream(owner->getColors(), 4);
    renderImageWorldSpace(position, getAngle(), scale, spriteSize, game->getRotation(), curFrame, numFrames, 0.0f);


    //UNCOMMENT TO DRAW DEBUG PRIMITIVES. Yellow circle = Unit Sight. Blue circle = Unit bounding volume
    CIwMat pMat = CIwMat::g_Identity;
    pMat.SetTrans(CIwVec3(position.x, -position.y, 1));
    CIwMat rot = CIwMat::g_Identity;
    rot.SetRotZ(IW_ANGLE_FROM_RADIANS(game->getRotation()));

    //IwGxDebugPrimCircle(pMat*rot, sight, 2,IwGxGetColFixed(IW_GX_COLOUR_YELLOW), false);
    //IwGxDebugPrimCircle(pMat*rot, getSize()/2.0, 2,IwGxGetColFixed(IW_GX_COLOUR_BLUE), false);

    
}

void Unit::displayOnScreen(int x, int y){    
    
    CIwMaterial *mat = new CIwMaterial();
    mat->SetTexture((CIwTexture*)game->getSprites()->GetResNamed(getTextureName(), IW_GX_RESTYPE_TEXTURE));
    mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
    mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
    IwGxSetMaterial(mat);
    
	CIwSVec2 xy(x-45, y-45);
    CIwSVec2 duv(IW_FIXED(1.0/numFrames), IW_GEOM_ONE);
    
	static CIwSVec2 wh(90, 90);
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

Unit* Unit::getTarget(){ return target; }
void Unit::setTarget(Unit* unit){
    target = unit; 
    if(target != NULL && target->getHp() <= 0)
        target = NULL;
}

bool Unit::hasTarget(){
    return target != NULL;
}


void Unit::setOwner(Player* p){
	owner = p;
    localPlayedOwnsThis = owner == game->getLocalPlayer();
}

float Unit::getHp(){ return hp; }
float Unit::getRange(){return range;}

void Unit::setHp(float f){
	hp = f;
}

float Unit::getSpeed(){return speed;}
float Unit::getSize(){ return spriteSize*scale; }


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

void Unit::attack(){}

int Unit::getDamage(Unit* unit){
    return 0;
}


void Unit::receiveDamage(float amount, Unit* attacker){
    if(hp <= amount){
        attacker->setTarget(NULL);
    }
    
    hp -= amount;
}

float Unit::distToTarget(){
    if(!hasTarget()) return -1;
    
    return (getTarget()->getPosition() - getPosition()).GetLength();
}
