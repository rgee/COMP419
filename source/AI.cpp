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
                unit->setVelocity(old_position - unit->getPosition());
            }
        } else {
            unit->setVelocity(pursuitVector);
        }
	}
	// If we are neither attacking, nor pursuing and there is no one to pursue,
	// head in the direction of the enemy base.
	else {
		float thetaChange = speed/rad;
        
		float tempTheta = thetaChange + theta;
        
		float old_theta = unit->getTheta();
		float old_r = unit->getR();
        CIwFVec2 tempPos(unit->getX(), unit->getY());

        unit->setPolarPosition(rad, tempTheta);
        unit->setVelocity(unit->getPosition() - tempPos);

        // Check if we would hit any other unit.
        std::list<Unit*> tempArray; 
		collide(std::back_inserter(tempArray), unit);

		// If we hit something, reset the movement.
        if (!tempArray.empty()) {
			unit->setPolarPosition(old_r, old_theta);
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

			sq_dist = SQ(temp_Pos.x - position.x) + SQ(temp_Pos.y - position.y);
			radii = SQ(((*itr)->getSize() + aggro_radii));
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

std::list<Unit*>* AI::collisionDetection(Unit* unit){
    float lowTheta = unit->getTheta()-10;
    float upTheta  = unit->getTheta()+10;
    float upRad  = worldRad.y;
    float lowRad = worldRad.x;

	std::list<Unit*>* Units = game->getUnits();
 
    CIwFVec2 pos = unit->getPosition()+unit->getVelocity();
    polarize(pos);
    
    float rad   = pos.x;
    float theta = pos.y;
    
    float size = unit->getSize();
	float current_unit_theta = 0.0f;
    
	float sq_dist = 0.0f;
	float radii = 0.0f;
   
    
    std::list<Unit*>* collide_array = new std::list<Unit*>();
    
    if((lowRad <= rad) && (rad <= upRad)){
        return NULL;
    }
    
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        Unit *temp = *itr;
		current_unit_theta = temp->getTheta();
        if((lowTheta <= current_unit_theta) && (current_unit_theta <= upTheta)){
            CIwFVec2 tempPos = temp->getPosition();

			// We can just use the squared distance here since we only care about relative
			// positioning.
            sq_dist = SQ(tempPos.x - pos.x) + SQ(tempPos.y - pos.y);
			radii = pow(size + temp->getSize(), 2);
            if (sq_dist <= radii) {
                collide_array->push_back(temp);
            }
        }
    }
    return collide_array;
}

template<typename OutputIterator> void AI::collide(OutputIterator out, Unit* unit)
{
	std::list<Unit*>* units = game->getUnits();

	float sq_dist = 0.0f;
	float radii = 0.0f;
	float bounding_radii = unit->getSize();
	CIwFVec2 position = unit->getPosition() + unit->getVelocity();
	CIwFVec2 temp_Pos = CIwFVec2::g_Zero;

	for(std::list<Unit*>::iterator itr = units->begin(); itr != units->end(); ++itr) {
		if(*(itr) != unit) {
			temp_Pos = (*itr)->getPosition();
			sq_dist = SQ(temp_Pos.x - position.x) + SQ(temp_Pos.y - position.y);
			radii = SQ(((*itr)->getSize() + bounding_radii));
			if(sq_dist < 0) sq_dist *= -1;
			if(sq_dist <= radii) {
				*(out++) = *(itr);
			}
		}
	}
}
 