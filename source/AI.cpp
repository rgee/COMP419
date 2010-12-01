#include "AI.h"
  
AI::AI(Game* game):game(game){
    worldRad = game->getWorldRadius();
}

void AI::path(Unit* unit){ 
	float rad = unit->getR();
	float theta = unit->getTheta();
	float speed = unit->getSpeed();
	float range = unit->getRange();

	// If we are neither attacking nor pursuing, find a unit to pursue
    if(!unit->attacking() && !unit->pursuing()){
        Unit *enemy;
        if((enemy = detectEnemy(unit)) != NULL){
            unit->setPursuing(enemy);
        }
    }

	// If we are attacking, continue attacking.
	if(unit->attacking()){
        attack(unit); 
	}

	// If we are pursuing, set our velocity to move toward our target.
	if(unit->pursuing()){ 
		Unit *pursuing = unit->getPursuing();
        CIwFVec2 old_position = unit->getPosition();
		CIwFVec2 pursuingPos = pursuing->getPosition();
		CIwFVec2 pursuitVector = pursuingPos - unit->getPosition();
        CIwFVec2 tempPos = CIwFVec2::g_Zero;

        // If we've reached attack range, attack.
		if (pursuitVector.GetLength() <= range) {
            attack(unit);
        }

        // We just set the velocity vector to face their target if
        // we're updating a stationary unit, otherwise, move them.
        if(speed > 0.0f) {
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
	}
	// If we are neither attacking, nor pursuing and there is no one to pursue,
	// head in the direction of the enemy base.
	else {
		
		CIwFVec2 polarVel = unit->getVelocity();
		polarize(polarVel);
		
		float thetaChange = speed/rad;
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
				
				tempArray.clear();
				unit->setPolarPosition(rad + rIncr, tempTheta);
				collide(std::back_inserter(tempArray), unit);
				
				if (tempArray.empty() && isInWorld(unit->getPosition(), worldRad.x, worldRad.y)) {
					foundDir = true;
					break;
				}
				else {
					tempArray.clear();
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
		
}
			
bool AI::attack(Unit* unit){
	if(!unit->attacking()){
        unit->setAttacking(unit->getPursuing());
	}
	if(unit->attacking() && unit->pursuing()){
		unit->setPursuing(NULL);
	}
    return false;
    
} 


Unit* AI::detectEnemy(Unit* unit){
    std::list<Unit*>* units = game->getUnits();
    CIwFVec2 position = unit->getPosition() + unit->getVelocity();
    CIwFVec2 temp_Pos = CIwFVec2::g_Zero;
    
    float closest_distance = 1000000.0f;
    float aggro_radii = unit->getSight();
    float sq_dist = 0.0f;
    float radii = 0.0f;
    Unit* closest =  NULL;
    

    // Just treat sight as a radius for now and return the closest enemy unit within it.
    for(std::list<Unit*>::iterator itr = units->begin(); itr != units->end(); ++itr) {
        if(&(*itr)->getOwner() != &unit->getOwner()) {
			temp_Pos = (*itr)->getPosition();

			sq_dist = sqrt(SQ(position.x - temp_Pos.x) + SQ(position.y - temp_Pos.y));
            radii = aggro_radii;
			if(sq_dist < 0) sq_dist *= -1;

            // Check if we've seen a nearer unit. If so, ignore this one and prefer the closer one.
			if(sq_dist <= radii && sq_dist <= closest_distance) {
                closest_distance = sq_dist;
                closest = *(itr);
			}
		}
	}
    return closest;
}
 
void AI::updateAI(Unit* unit){
     path(unit);
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
