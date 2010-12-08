#include "unit.h"
#include "IwGeom.h"

Unit::Unit(const Unit& newUnit)
	: WorldObject(newUnit), 
	hp(newUnit.hp), cost(newUnit.cost), attackDamage(newUnit.attackDamage), speed(newUnit.speed),
	munch_speed(newUnit.munch_speed), range(newUnit.range), sight(newUnit.sight),
	spread_speed(newUnit.spread_speed), spread_radius(newUnit.spread_radius),
	scale(newUnit.scale), target(NULL), curFrame(0), numFrames(newUnit.numFrames), spriteSize(newUnit.spriteSize),
	navTarget(CIwFVec2(0, 0)), repulsion_factor(1)
{
	setOwner(newUnit.owner);
	navTarget = CIwFVec2::g_Zero;
	enemyLeaderPos = ((Unit*)(game->getOpponentPlayer()->getLeader()))->getPosition();
	isDodgePathing = false;
}

Unit::Unit(float hp, float cost, float attack, float speed, 
		float munch_speed, float range, float sight,
		float spread_speed, float spread_radius, Player* owner,
		Game* game)
		: WorldObject(game),
		  hp(hp), cost(cost), attackDamage(attack), speed(speed),
		  munch_speed(munch_speed), range(range), sight(sight),
		  spread_speed(spread_speed), spread_radius(spread_radius),
		  curFrame(0), target(NULL), navTarget(CIwFVec2(0, 0)), repulsion_factor(1)
{
    setOwner(owner);
	navTarget = CIwFVec2::g_Zero;
	enemyLeaderPos = ((Unit*)(game->getOpponentPlayer()->getLeader()))->getPosition();
	isDodgePathing = false;
}

void Unit::display(){
	IwGxSetColStream(owner->getColors(), 4);
    renderImageWorldSpace(position, getAngle(), scale, spriteSize, game->getRotation(), curFrame, numFrames, 0.0f);

    //UNCOMMENT TO DRAW DEBUG PRIMITIVES. Yellow circle = Unit Sight. Blue circle = Unit bounding volume
    
	/*CIwFVec2 circle = navTarget;
	polarize(circle);
	circle.y *= -1;
	polarToXY(circle);
	
    CIwMat pMat = CIwMat::g_Identity;
    pMat.SetTrans(CIwVec3(circle.x, circle.y, 1));
    CIwMat rot = CIwMat::g_Identity;
    rot.SetRotZ(IW_ANGLE_FROM_RADIANS(game->getRotation()));

	if (getType() == MUNCHER) {
		IwGxDebugPrimCircle(pMat*rot, 20, 2, IwGxGetColFixed(IW_GX_COLOUR_BLUE), false);
	}
    //IwGxDebugPrimCircle(pMat*rot, sight, 2,IwGxGetColFixed(IW_GX_COLOUR_YELLOW), false);*/
     
}

void Unit::displayOnScreen(int x, int y){    
    
    CIwMaterial *mat = new CIwMaterial();
	mat->SetTexture((CIwTexture*)game->getSprites()->GetResHashed(getTextureName(), IW_GX_RESTYPE_TEXTURE));
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


Player& Unit::getOwner(){
	return *owner;
}

Unit* Unit::getTarget(){ return target; }
void Unit::setTarget(Unit* unit){
    if(unit != NULL && unit->getHp() <= 0) {
        target = NULL;
	} else {
		target = unit;
	}
	if(target == NULL) {
		setIdleSprite();
	}
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

void Unit::path(std::list<Unit*>::iterator itr) {
	
	std::list<Unit*>* units = game->getUnits();
	
	CIwFVec2 force = CIwFVec2::g_Zero; //sum of all forces on this unit
	
	CIwFVec2 dirToward = CIwFVec2::g_Zero; //vector from repelling unit to this unit
	Unit* curUnit; //current repelling unit
	
	//sum up all of the repulsive forces on this unit
	for (itr = units->begin() ; itr != units->end(); ++itr) {
		curUnit = *(itr);
		
		if ((*itr) != this && THETA_DIFF(curUnit->getTheta(), theta) < PATH_THETA_RANGE) {
			dirToward = position - curUnit->getPosition();
			float dist = dirToward.GetLengthSquared();
			force += dirToward.GetNormalised() * (repulsion_factor * curUnit->getSize()*REPEL_FACTOR / pow(dist, 1.875));
            // We can tweak bottom factor later, this seems to work fine:           ^
		}
	}
	
	CIwFVec2 toLeader = (enemyLeaderPos-position).GetNormalised();
	CIwFVec2 toLeaderPolar = toLeader;
	polarize(toLeaderPolar);
	float dodgeThetaIncr = toLeaderPolar.y < 0 ? .3 : -.3;
	
	//if not dodge pathing, add circular pathing force
	if(!isDodgePathing) {
		float centerR = (game->getWorldRadius().y + game->getWorldRadius().x)/2.0;
		float rDiff = centerR - r;
		force += position * ((rDiff < 0 ? -1 : 1) * WALL_REPEL * SQ(rDiff)); // Ternary is experimentally faster
		force += LEADER_ATTRACTION * toLeader;
	}
	
	if (!isDodgePathing && force.GetLengthSquared() < FORCE_THRESHOLD) {
		CIwFVec2 worldRad = game->getWorldRadius();
		float innerDist = getR() - worldRad.x;
		float outerDist = worldRad.y - getR();
	
		float targetR;
		
		if (innerDist > outerDist) {
			targetR = worldRad.x + getSize()/2;
		}
		else {
			targetR = worldRad.y - getSize()/2;
		}
		
		navTargetPolar = CIwFVec2(targetR, getTheta() + dodgeThetaIncr);
		navTarget = navTargetPolar;
		polarToXY(navTarget);					
		isDodgePathing = true;
	}
	
	if (isDodgePathing) {
		/*char* str = (char*)malloc(sizeof(char)*100);
		sprintf(str, "%f", force.GetLengthSquared());
		s3eDebugOutputString(str);
		free(str);*/
		
		force += NAV_ATTRACT_FACTOR * (navTarget-position).GetNormalised();
		
		CIwFVec2 navVec = (navTarget - position);
		CIwFVec2 enemyLeaderDir = (enemyLeaderPos - position).GetNormalised();
		float dot = (force.GetNormalised()).Dot(enemyLeaderDir);
		
		if (dot > cos(PI/4) || navVec.GetLengthSquared() < 1000) {
			isDodgePathing = false;
		}
		else {
			navTargetPolar.y = getTheta() + dodgeThetaIncr;
			navTarget = navTargetPolar;
			polarToXY(navTarget);
		}
	}
	
	velocity = speed * force.GetNormalised();
	setPosition(position + velocity);
}

