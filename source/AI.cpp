#include "AI.h"
  
AI::AI(Game* game):game(game){
    worldRad = game->getWorldRadius();
}

void AI::path(Unit* unit){ 
	float rad = unit->getR();
	float theta = unit->getTheta();
	float speed = unit->getSpeed();
	float range = unit->getRange();
    if(!unit->attacking() && !unit->pursuing()){
        Unit *Enemy = detectEnemy(unit, unit->getGame()->getUnits());
        if(Enemy != NULL){
            unit->setPursuing(Enemy);
        }
    }
	if(unit->attacking())
        attack(unit); 
    
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
            unit->setVelocity(CIwFVec2::g_Zero);}
	}
	else {
		float thetaChange = speed/rad;
		float tempTheta = thetaChange + theta;

        unit->setPolarPosition(rad, tempTheta);
        CIwFVec2 tempPos = unit->getPosition();
        unit->setPolarPosition(rad, theta);
        unit->setVelocity(tempPos-unit->getPosition());

        
        std::list<Unit*> tempArray; 
		collide(std::back_inserter(tempArray), unit);
        if (!tempArray.empty()) {
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


Unit* AI::detectEnemy(Unit* unit, std::list<Unit*>* Units){
	float sight = unit->getSight();
    float lowTheta = unit->getTheta()-sight;
    float upTheta = unit->getTheta()+sight;
    CIwFVec2 Pos = unit->getPosition()+unit->getVelocity();
	float current_unit_theta;
    float minDist=1000;
    Unit *Enemy;
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        Unit *temp = *itr;
		current_unit_theta = temp->getTheta();
		if( (lowTheta <= current_unit_theta) && (current_unit_theta <= upTheta)){
            CIwFVec2 tempPos = temp->getPosition();
            float dist = sqrt((tempPos.x+Pos.x)*(tempPos.x+Pos.x)+(tempPos.y+Pos.y)*(tempPos.y+Pos.y));
            if (dist<=minDist) {
                minDist = dist;
                Enemy = temp;
            }
        }
    }
    return Enemy;

}
 
void AI::updateAI(Unit* unit){
     //path(unit);
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
   
    
    if(lowRad <= rad <= upRad){
        return;
    }
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        Unit *temp = *itr;
        if(lowTheta <= temp->getTheta() <= upTheta){
            CIwFVec2 tempPos = temp->getPosition();

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
 