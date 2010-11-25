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
		CIwFVec2 pursuingPos = pursuing->getPosition();
		CIwFVec2 pursuitVector = pursuingPos - unit->getPosition();
		CIwFVec2 tempPos; 
		if (pursuitVector.GetLength()<range)
            attack(unit);
		tempPos = (pursuitVector/speed)+unit->getPosition();
        unit->setVelocity(tempPos-unit->getPosition());

		
        std::list<Unit*> tempArray;
		collide(std::back_inserter(tempArray), unit);
        
        if (!tempArray.empty()){
            unit->setVelocity(CIwFVec2::g_Zero);
		}
	}
	// If we are neither attacking, nor pursuing and there is no one to pursue,
	// head in the direction of the enemy base.
	else {
		float thetaChange = speed/rad;
		float tempTheta = thetaChange + theta;
        
        CIwFVec2 tmpPos(unit->getX(), unit->getY());

        unit->setPolarPosition(rad, tempTheta);
        unit->setVelocity(unit->getPosition() - tmpPos);

        // Check if we would hit any other unit.
        std::list<Unit*> tempArray; 
		collide(std::back_inserter(tempArray), unit);

		// If we hit something, reset the movement.
        if (!tempArray.empty()) {
			unit->setPolarPosition(rad, theta);
            unit->setVelocity(CIwFVec2::g_Zero);
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
	std::list<Unit*>* Units = game->getUnits();
	float sight = unit->getSight();
    float lowTheta = unit->getTheta()-sight;
    float upTheta = unit->getTheta()+sight;
    CIwFVec2 Pos = unit->getPosition()+unit->getVelocity();
	float current_unit_theta;

	// Remember, this is squared distace.
    float minDist=pow(1000, 2);
	float sq_dist = 0.0f;

    Unit *Enemy;
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
		if(!(&(*itr)->getOwner() == &unit->getOwner())) {
			Unit *temp = *itr;
			current_unit_theta = temp->getTheta();
			if( (lowTheta <= current_unit_theta) && (current_unit_theta <= upTheta)){
				CIwFVec2 tempPos = temp->getPosition();
				sq_dist = (tempPos.x+Pos.x)*(tempPos.x+Pos.x)+(tempPos.y+Pos.y)*(tempPos.y+Pos.y);
				if (sq_dist <=minDist) {
					minDist = sq_dist;
					Enemy = temp;
				}
			}
		}
    }
    return Enemy;

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
 
    CIwFVec2 Pos = unit->getPosition()+unit->getVelocity();
    polarize(Pos);
    float rad = Pos.x;
    float theta = Pos.y;
    float size = unit->getSize();
	float current_unit_theta = 0.0f;
	float sq_dist = 0.0f;
	float radii = 0.0f;
   
    
    std::list<Unit*>* collide_array = new std::list<Unit*>();
    if((lowRad <= rad) && (lowRad <= upRad)){
        return NULL;
    }
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        Unit *temp = *itr;
		current_unit_theta = temp->getTheta();
        if((lowTheta <= current_unit_theta) && (current_unit_theta <= upTheta)){
            CIwFVec2 tempPos = temp->getPosition();

			// We can just use the squared distance here since we only care about relative
			// positioning.
            sq_dist = (tempPos.x+Pos.x)*(tempPos.x+Pos.x)+(tempPos.y+Pos.y)*(tempPos.y+Pos.y);
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
	std::list<Unit*>* Units = game->getUnits();


	float lowTheta = unit->getTheta()-10;
    float upTheta  = unit->getTheta()+10;
    float upRad  = worldRad.y;
    float lowRad = worldRad.x;
 
    CIwFVec2 Pos = unit->getPosition()+unit->getVelocity();
    polarize(Pos);

    float rad = Pos.x;
    float theta = Pos.y;
    float size = unit->getSize();
	float sq_dist = 0.0f;
	float radii = 0.0f;
	float current_unit_theta = 0.0f;
	CIwFVec2 tempPos = CIwFVec2::g_Zero;
	Unit* temp;
    
    if((lowRad <= rad) && (lowRad <= upRad)){
        return;
    }
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        temp = *itr;
		current_unit_theta = temp->getTheta();
        if((lowTheta <= current_unit_theta) && (current_unit_theta <= upTheta)){
            tempPos = temp->getPosition();

			// We can just use the squared distance here since we only care about relative
			// positioning.
            sq_dist = (tempPos.x+Pos.x)*(tempPos.x+Pos.x)+(tempPos.y+Pos.y)*(tempPos.y+Pos.y);
			radii = pow(size + temp->getSize(), 2);
            if (sq_dist <= radii) {
				*(out++) = temp;
            }
        }
    }

}
 