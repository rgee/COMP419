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

		
        std::list<Unit*> *tempArray = collisionDetection(unit, unit->getGame()->getUnits());
        
        if (tempArray == NULL || !tempArray->empty()){
            unit->setVelocity(CIwFVec2::g_Zero);}

        
        delete tempArray;
	}
	else {
		float thetaChange = speed/rad;
		float tempTheta = thetaChange + theta;

        unit->setRTheta(rad, tempTheta);
        CIwFVec2 tempPos = unit->getPosition();
        unit->setRTheta(rad, theta);
        unit->setVelocity(tempPos-unit->getPosition());

        
        std::list<Unit*> *tempArray = collisionDetection(unit, unit->getGame()->getUnits());
        if (tempArray == NULL || !tempArray->empty()) {

            unit->setVelocity(CIwFVec2::g_Zero);

        }
        delete tempArray;
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
    float minDist=1000;
    Unit *Enemy;
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        Unit *temp = *itr;
        if(lowTheta <= temp->getTheta() <= upTheta){
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

std::list<Unit*>* AI::collisionDetection(Unit* unit, std::list<Unit*>* Units){
    float lowTheta = unit->getTheta()-10;
    float upTheta  = unit->getTheta()+10;
    float upRad  = worldRad.y;
    float lowRad = worldRad.x;
 
    CIwFVec2 Pos = unit->getPosition()+unit->getVelocity();
    float rad = unit->ConvertToRTheta(Pos).x;
    float theta = unit->ConvertToRTheta(Pos).y;
    float size = unit->getSize();

   
    
    std::list<Unit*>* collide_array = new std::list<Unit*>();
    if(lowRad <= rad <= upRad){
        return NULL;
    }
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        Unit *temp = *itr;
        if(lowTheta <= temp->getTheta() <= upTheta){
            CIwFVec2 tempPos = temp->getPosition();
            float dist = sqrt((tempPos.x+Pos.x)*(tempPos.x+Pos.x)+(tempPos.y+Pos.y)*(tempPos.y+Pos.y));
            if (dist<=(size+temp->getSize())) {
                collide_array->push_back(temp);
            }
        }
    }
    return collide_array;
}
 