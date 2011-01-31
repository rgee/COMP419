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

	pathMode = NORMAL;
	if(speed > 0.00001f) {
		if (owner == game->getLocalPlayer()) {
			enemyLeaderPos = ((Unit*)(game->getOpponentPlayer()->getLeader()))->getPosition();
		}
		else {
			enemyLeaderPos = ((Unit*)(game->getLocalPlayer()->getLeader()))->getPosition();
		}
	}
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

	pathMode = NORMAL;
	if(speed > 0.00001f) {
		if (owner == game->getLocalPlayer()) {
			enemyLeaderPos = ((Unit*)(game->getOpponentPlayer()->getLeader()))->getPosition();
		}
		else {
			enemyLeaderPos = ((Unit*)(game->getLocalPlayer()->getLeader()))->getPosition();
		}
	}
}

int Unit::getDamage(Unit* unit){
	return (int) statAttacks[unit->getType()][getType()];
}



void Unit::display(){
	IwGxSetColStream(owner->getColors(), 4);
    renderImageWorldSpace(position, getAngle(), scale, spriteSize, game->getRotation(), curFrame, numFrames, 0.0f);

    //UNCOMMENT TO DRAW DEBUG PRIMITIVES. Yellow circle = Unit Sight. Blue circle = Unit bounding volume
    
	CIwFVec2 circle = navTarget;
	polarize(circle);
	circle.y *= -1;
	polarToXY(circle);
	
    CIwMat pMat = CIwMat::g_Identity;
    pMat.SetTrans(CIwVec3(circle.x, circle.y, 1));
    CIwMat rot = CIwMat::g_Identity;
    rot.SetRotZ(IW_ANGLE_FROM_RADIANS(game->getRotation()));

	if (getType() == MUNCHER) {
		//IwGxDebugPrimCircle(pMat*rot, 20, 2, IwGxGetColFixed(IW_GX_COLOUR_BLUE), false);
	}
    //IwGxDebugPrimCircle(pMat*rot, sight, 2,IwGxGetColFixed(IW_GX_COLOUR_YELLOW), false);
     
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
	
	if (localPlayedOwnsThis) {
		enemyLeaderPos = ((Unit*)(game->getOpponentPlayer()->getLeader()))->getPosition();
	}
	else {
		enemyLeaderPos = ((Unit*)(game->getLocalPlayer()->getLeader()))->getPosition();
	}
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
	
	// Normalized vector from this unit to the enemy leader. 
	// Need this for normal pathing and escape pathing.
	CIwFVec2 toLeader = (enemyLeaderPos-position).GetNormalised();
	
	CIwFVec2 repulsionSum = CIwFVec2::g_Zero;
	
	/********************************
	 **** Begin Force Calculation ***
	 ********************************/
	
	
	std::list<Unit*>* units = game->getUnits(); //all the units in the game
	CIwFVec2 force = CIwFVec2::g_Zero; //sum of all forces on this unit
	CIwFVec2 dirToward = CIwFVec2::g_Zero; //vector from current repelling unit to this unit
	Unit* curUnit; //current repelling unit in loop
	
	//sum up all of the repulsive forces on this unit
	for (itr = units->begin() ; itr != units->end(); ++itr) {
		curUnit = *(itr);
		
		if (curUnit != this && curUnit->getType() != PROJECTILE) {
			dirToward = position - curUnit->getPosition();
			float dist = dirToward.GetLengthSquared();
			repulsionSum += dirToward.GetNormalised() * (repulsion_factor * curUnit->getSize()*REPEL_FACTOR / pow(dist, 1.875));
		}
	}
	
	force += repulsionSum;

	if (pathMode == OBJECTIVE) {
		if (target != NULL) {
			navTarget = target->getPosition();
		}
		else {
			pathMode = NORMAL;
		}

	}
	
	// if not escape pathing, add at least the circular pathing force 
	if(pathMode != ESCAPE) {
		float rDiff = (game->getWorldRadius().y + game->getWorldRadius().x)/2.0 - r;
		force += position * ((rDiff < 0 ? -1 : 1) * CIRCLE_SPRING * SQ(rDiff)); // Ternary is experimentally faster
		
		// only add enemy leader force if doing normal pathing
		if (pathMode == NORMAL) {
			force += LEADER_ATTRACTION * toLeader;
		}
	}
	
	// if in a special pathing mode, add force toward the navigation target
	if (pathMode != NORMAL) {
		force += NAV_ATTRACT_FACTOR * (navTarget-position).GetNormalised();
	}
	
	// if we're running into walls, add their normal force to the sum
	CIwFVec2 worldRad = game->getWorldRadius();
	float unitRad = getSize()/2;
	float toInner = getR() - worldRad.x,
	toOuter = worldRad.y - getR();
	
	/********************************
	 **** End Force Calculation *****
	 ********************************/
	
	if (force.GetLengthSquared() < FORCE_THRESHOLD) {
		setEscapeTarget(toLeader, force);
	}

	if (pathMode == ESCAPE) {
		CIwFVec2 normal = (CIwFVec2(-force.y, force.x)).GetNormalised();
		CIwFVec2 repulsionNorm = repulsionSum.GetNormalised();
		CIwFVec2 normalForce = repulsionSum * normal.Dot(repulsionNorm);
		
		if (normalForce.GetLengthSquared() < NORMAL_FORCE_THRESHOLD) {
			pathMode = NORMAL;
		}
		else {
			setEscapeTarget(toLeader, force);
		}

	}
	
	if (toInner <= unitRad) {
		CIwFVec2 normal = CIwFVec2(cos(getTheta()), sin(getTheta()));
		float dot = force.GetNormalised().Dot(-1 * normal);
		force += normal * (dot > 0 ? dot : 0) * force.GetLength();
		if(pathMode == ESCAPE) setEscapeTarget(toLeader, force);
	}
	else if(toOuter <= unitRad) {
		CIwFVec2 normal = CIwFVec2(-cos(getTheta()), -sin(getTheta()));
		float dot = force.GetNormalised().Dot(-1 * normal);
		force += normal * (dot > 0 ? dot : 0) * force.GetLength();
		if(pathMode == ESCAPE) setEscapeTarget(toLeader, force);
	}
	
	if (pathMode == OBJECTIVE && (navTarget-position).GetLengthSquared() <= SQ(range)) {
		s3eDebugOutputString("made it!");
		velocity = force.GetNormalised();
	}
	else {
		float curSpeed = 10 * speed * force.GetLengthSquared()/(SQ(LEADER_ATTRACTION));
		curSpeed = (curSpeed <= speed) ? curSpeed : speed;
		velocity = curSpeed * force.GetNormalised();
		setPosition(position + velocity);
	}
}

									   
// Create a navigation target at the wall furthest from this
// unit, slightly ahead of it's current theta position.
void Unit::setEscapeTarget(CIwFVec2 toLeader, CIwFVec2 force) {	
	
	float thetaDir; //the "forward" direction toward the enemy base
	
	if (owner == game->getLocalPlayer()) {
		thetaDir = getTheta() > 0 ? 1 : -1;
	}
	else {
		thetaDir = getTheta() > PI ? 1 : -1;
	}

	CIwFVec2 worldRad = game->getWorldRadius();
	float innerDist = getR() - worldRad.x;
	float outerDist = worldRad.y - getR();
	
	// if already escape pathing, don't change the target wall, else
	// figure out which wall is the furthest from us, and go to it
	if (pathMode != ESCAPE) {
		if (innerDist > outerDist) {
			navTarget.x = worldRad.x - getSize();
		}
		else {
			navTarget.x = worldRad.y + getSize();
		}
		
		navTarget.y = getTheta() + .3 * thetaDir; 
		polarToXY(navTarget);
	}
	else {
		polarize(navTarget);
		navTarget.y += .01 * thetaDir * (force.GetLengthSquared() < SQ(NAV_ATTRACT_FACTOR) ? -1 : (PI - abs(getTheta())) * 10);
		polarToXY(navTarget);
	}
	
	pathMode = ESCAPE;
}


void Unit::detectEnemy(std::list<Unit*>::iterator unit_itr) {
    std::list<Unit*>* units = game->getUnits();
    CIwFVec2 position = (*unit_itr)->getPosition() + (*unit_itr)->getVelocity();
    CIwFVec2 otherPos = CIwFVec2::g_Zero;
    
    float sq_dist = 0;
    float closest_distance = SQ((*unit_itr)->getSight());
    float max_dist = closest_distance;
    Unit* closest = (*unit_itr)->getTarget();
	
	bool foundTarget = false;
    
    /**
	* In order to avoid brute-force distance calculations, we take advantage of
	* the fact that the units are sorted by their theta values. We begin our distance
	* checking at the given unit's position in the sorted container, then at each
	* step, check the unit with the next nearest theta, and see if it's close enough.
	* 
	* We stop once we've reached a unit that is completely outside the sight range,
	* We do the same thing in both directions to find the closest unit.
	*/
    std::list<Unit*>::iterator incr_theta_itr = unit_itr;
    std::list<Unit*>::iterator decr_theta_itr = unit_itr;
    
    incr_theta_itr++;
    
    while(incr_theta_itr != unit_itr && sq_dist <= max_dist) {
	// Look up theta, which means we're moving to the BACK of the container
		if(&(*incr_theta_itr)->getOwner() != &(*unit_itr)->getOwner()) {
			otherPos = (*incr_theta_itr)->getPosition();
			sq_dist = SQ(position.x - otherPos.x) + SQ(position.y - otherPos.y);
			
			if(sq_dist < closest_distance && (*decr_theta_itr)->getHp() > 0 && (*incr_theta_itr)->getType() != PROJECTILE) {
				closest_distance = sq_dist;
				closest = *incr_theta_itr;
				foundTarget = true;
			}
		}
        
        incr_theta_itr++;
        if(incr_theta_itr == units->end()) incr_theta_itr = units->begin();
	}

	// Must reset the distance here since we're switching directions.
	sq_dist = 0.0f;
    while(incr_theta_itr != decr_theta_itr && sq_dist <= max_dist) {
		// Look down theta, which means we're moving to the FRONT of the container. 
		if(&(*decr_theta_itr)->getOwner() != &(*unit_itr)->getOwner()) {
			otherPos = (*decr_theta_itr)->getPosition();
			sq_dist = SQ(position.x - otherPos.x) + SQ(position.y - otherPos.y);
			
			if(sq_dist < closest_distance && (*decr_theta_itr)->getHp() > 0 && (*decr_theta_itr)->getType() != PROJECTILE) {
				closest_distance = sq_dist;
				closest = *(decr_theta_itr);
				foundTarget = true;
			}
		}

        if(decr_theta_itr == units->begin()) decr_theta_itr = units->end();
        decr_theta_itr--;

	}
	
	
	target = closest;
	
	if (foundTarget) {
		s3eDebugOutputString("found target");
		pathMode = OBJECTIVE;
	}
}

