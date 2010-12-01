#include "AI.h"
  
AI::AI(Game* game):game(game){
    worldRad = game->getWorldRadius();
}

void AI::doIdle(Unit* unit) {
    unit->setPursuing(detectEnemy(unit));
    if(unit->pursuing()) {
        unit->setAIState(PURSUING);
		return;
    }

    float rad = unit->getR();
	float speed = unit->getSpeed();
	float range = unit->getRange();
    float theta = unit->getTheta();
    CIwFVec2 polarVel = unit->getVelocity();
	polarize(polarVel);
        
    Player *p = game->getLocalPlayer();
    Player *q = &unit->getOwner();
    float targetTheta = (p == q) ? 0 : PI;
        
    int direction = -1;
    float diff = theta - targetTheta; // so theta or theta - PI
        
    if(diff < PI && diff > 0) direction = 1;
		
	float thetaChange = direction*speed/rad;
	float tempTheta = thetaChange + theta;
        
	float curR = unit->getR(); 
	float curTheta = unit->getTheta();
	CIwFVec2 curPos = unit->getPosition();
		
	CIwFVec2 curPolarPos = curPos;
	polarize(curPolarPos);
		

    unit->setPolarPosition(rad, tempTheta);
    unit->setVelocity(unit->getPosition() - curPos);

    // Check if we would hit any other unit.
    std::list<Unit*> tempArray; 
	collide(std::back_inserter(tempArray), unit);

	// If we hit something, reset the movement.
    if (!tempArray.empty()) {
			
		float rIncr;
			
		bool foundDir = false;
			
		for (rIncr = 0.0; rIncr < 30.0; rIncr += 5) {
			unit->setPolarPosition(rad + rIncr, tempTheta);
			collide(std::back_inserter(tempArray), unit);
				
			if (tempArray.empty() && isInWorld(unit->getPosition(), worldRad.x, worldRad.y)) {
				foundDir = true;
				break;
			}
			else {
				unit->setPolarPosition(rad - rIncr, tempTheta);
				collide(std::back_inserter(tempArray), unit);
					
				if (tempArray.empty() && isInWorld(unit->getPosition(), worldRad.x, worldRad.y)) {
					foundDir = true;
					break;
				}
			}
		}
			
		if (!foundDir) {
				
			float unitSize = unit->getSize();
				
			CIwFVec2 nextMoveOut = curPolarPos + CIwFVec2(20.0, 0.0);
			CIwFVec2 nextMoveIn = curPolarPos + CIwFVec2(-20.0, 0.0);

			polarToXY(nextMoveIn);
			polarToXY(nextMoveOut);
				
			if (isInWorld(nextMoveIn, worldRad.x, worldRad.y)) {
				unit->setPolarPosition(rad-20.0, theta);
			}
			else if (isInWorld(nextMoveOut, worldRad.x, worldRad.y)) {
				unit->setPolarPosition(rad+20.0, theta);
			}
			else {
				//unit->setPolarPosition(rad, theta-thetaChange);
			}
		}
					
		unit->setVelocity(unit->getPosition() - curPos);
    }
}


Unit* AI::detectEnemy(Unit* unit){
    std::list<Unit*>* units = game->getUnits();
    CIwFVec2 position = unit->getPosition() + unit->getVelocity();
    CIwFVec2 temp_Pos = CIwFVec2::g_Zero;
    
    float aggro_radii = unit->getSight();
    float sq_dist = 0.0f;
    float closest_distance = SQ(aggro_radii);
    Unit* closest =  NULL;
    

    // Just treat sight as a radius for now and return the closest enemy unit within it.
    for(std::list<Unit*>::iterator itr = units->begin(); itr != units->end(); ++itr) {
        if(&(*itr)->getOwner() != &unit->getOwner()) {
			temp_Pos = (*itr)->getPosition();
			sq_dist = SQ(position.x - temp_Pos.x) + SQ(position.y - temp_Pos.y);

            // Check if we've seen a nearer unit. If so, ignore this one and prefer the closer one.
			if(sq_dist <= closest_distance) {
                closest_distance = sq_dist;
                closest = *(itr);
			}
		}
	}

    return closest;
}
 
void AI::updateAI(Unit* unit){
    switch(unit->getAIState()) {
    case IDLE:
        doIdle(unit);
        break;
    case PURSUING:
        doPursue(unit);
        break;
    case ATTACKING:
        doAttack(unit);
        break;
    default:
        break;
    }
}

void AI::doAttack(Unit* unit) {
    float attacker_distance = (unit->getAttacking()->getPosition() - unit->getPosition()).GetLength();
    float attack_range = unit->getRange();

    // If the target is out of range, look for a nearer target.
    //
    // Units don't chase targets if there are nearer ones, currently. This is so we don't
    // completely strand shooters, who can't actually pursue, but will stay fixated on
    // an enemy they can't hit.
    //
    // This is also an example of why we may want units to do their own AI.
    if(attacker_distance >= attack_range) {
        unit->setAIState(PURSUING);
        unit->setPursuing(detectEnemy(unit));
        return;
    }
    unit->attack();
}

void AI::doPursue(Unit* unit) {
    unit->setPursuing(detectEnemy(unit));
    
    if(unit->pursuing()) {

        float speed = unit->getSpeed();
        float range = unit->getRange();
		Unit *pursuing = unit->getPursuing();
        CIwFVec2 old_position = unit->getPosition();
		CIwFVec2 pursuingPos = pursuing->getPosition();
		CIwFVec2 pursuitVector = pursuingPos - unit->getPosition();
        CIwFVec2 tempPos = CIwFVec2::g_Zero;

        // If we've reached attack range, attack.
		if (pursuitVector.GetLength() <= range) {
            unit->setAIState(ATTACKING);
            return;
        }

        // We just set the velocity vector to face their target if
        // we're updating a stationary unit, otherwise, move them.
        if(speed > 0.01f) { // use a small number because floats are imprecise
		    tempPos = (pursuitVector/speed) + unit->getPosition();

            unit->setPosition(tempPos);

            std::list<Unit*> tempArray;
		    collide(std::back_inserter(tempArray), unit);
        
            if (!tempArray.empty()){
                unit->setPosition(old_position);
		    } else {
                unit->setVelocity(unit->getPosition() - old_position);
            }
        } else {
            unit->setVelocity(pursuitVector);
        }
    } else {
        // If we were pursuing, and lost our target, return to idle.
        unit->setAIState(IDLE);
    }
}

template<typename OutputIterator> void AI::collide(OutputIterator out, Unit* unit)
{
	std::list<Unit*>* units = game->getUnits();
	
	CIwFVec2 unitPos = unit->getPosition();
	
	Unit* collideUnit; //unit that we're colliding with
	float collideRad; //radius of circle containing the colliding unit
	float unitRad = unit->getSize()/2.0;
    CIwFVec2 collidePos = CIwFVec2::g_Zero;
    CIwFVec2 collideDir = CIwFVec2::g_Zero;
    CIwFVec2 collideRadPoint = CIwFVec2::g_Zero;
    float collideT = 0.0f;
	
	for(std::list<Unit*>::iterator itr = units->begin(); itr != units->end(); ++itr) {
		
		if(*(itr) != unit) {
			collideUnit = *(itr);
			collideRad = collideUnit->getSize()/2.0;
			
			collidePos = collideUnit->getPosition(); //position of unit we're colliding with
			collideDir = (collidePos - unitPos); //normalized vector pointing from the unit toward the one being collided with
			collideDir.Normalise();
			
			collideRadPoint = (-1*collideDir)*collideRad + collidePos; //point on edge of colliding unit's bounding circle closest to our unit
				
			collideT = (collideRadPoint.x - unitPos.x)/collideDir.x;
			
			if (collideT <= unitRad) {
				*(out++) = collideUnit;
			}
		}
	}
}
