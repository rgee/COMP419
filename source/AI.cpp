
#include "AI.h"
  
AI::AI(){}

void AI::Path(Unit& unit){ 
	float rad = unit.getR();
	float theta = unit.getTheta();
	float speed = unit.getSpeed();
	float range = unit.getRange();
	 
	if(unit.attacking()){Attack(unit);};
	if(unit.pursuing()){ 
		Unit *pursuing = unit.getPursuing();
		CIwSVec2 pursuingPos = pursuing->getPosition();
		CIwSVec2 pursuitVector = pursuingPos - unit.getPosition();
		CIwSVec2 tempPos; 
		if (pursuitVector.GetLength()<range) {Attack(unit);}
		tempPos = (pursuitVector/speed)+unit.getPosition();
        unit.setVelocity(tempPos-unit.getPosition());
		
        std::list<Unit*> *tempArray = CollisionDetection(unit, unit.getGame()->getUnits());
         if (tempArray == NULL || !tempArray->empty()) {
            unit.setVelocity(CIwSVec2::g_Zero);
        }
        delete tempArray;
	}
	else {
		Unit *Enemy = Detect_Enemy(unit, unit.getGame()->getUnits());
		float thetaChange = speed/rad;
		float tempTheta = thetaChange + theta;
        unit.setRTheta(rad, tempTheta);
        CIwSVec2 tempPos = unit.getPosition();
        unit.setRTheta(rad, theta);
        unit.setVelocity(tempPos-unit.getPosition());
        
        std::list<Unit*> *tempArray = CollisionDetection(unit, unit.getGame()->getUnits());
        if (tempArray == NULL || !tempArray->empty()) {
            unit.setVelocity(CIwSVec2::g_Zero);
        }
        delete tempArray;
	}
		
}
			
bool AI::Attack(Unit& unit){
	if(!unit.attacking()){
	unit.setAttacking(unit.getPursuing());
	}
	if(unit.attacking() && unit.pursuing()){
		unit.setPursuing(NULL);
	}
    return false;
    
} 
Unit* AI::Detect_Enemy(Unit& unit, std::list<Unit*>* Units){
	float sight = unit.getSight();
    float lowTheta = unit.getTheta()-sight;
    float upTheta = unit.getTheta()+sight;
    CIwSVec2 Pos = unit.getPosition()+unit.getVelocity();
    float minDist=1000;
    Unit *Enemy;
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        Unit *temp = *itr;
        if(lowTheta <= temp->getTheta() <= upTheta){
            CIwSVec2 tempPos = temp->getPosition();
            float dist = sqrt((tempPos.x+Pos.x)*(tempPos.x+Pos.x)+(tempPos.y+Pos.y)*(tempPos.y+Pos.y));
            if (dist<=minDist) {
                minDist = dist;
                Enemy = temp;
            }
        }
    }
    return Enemy;

}

void AI::UpdateAI(Unit& unit){
	Path(unit);
	
}
std::list<Unit*>* CollisionDetection(Unit& unit, std::list<Unit*>* Units){
    float lowTheta = unit.getTheta()-10;
    float upTheta = unit.getTheta()+10;
    float upRad = unit.getGame()->getWorldRadius().y;
    float lowRad = unit.getGame()->getWorldRadius().x;
    
    CIwSVec2 Pos = unit.getPosition()+unit.getVelocity();
    float rad = unit.ConvertToRTheta(Pos).x;
    float theta = unit.ConvertToRTheta(Pos).y;
    float size = unit.getSize();
   
    
    std::list<Unit*>* collide_array = new std::list<Unit*>();
    if(lowRad <= rad <= upRad){
        return NULL;
    }
    for(std::list<Unit*>::iterator itr = Units->begin(); itr != Units->end(); itr++){
        Unit *temp = *itr;
        if(lowTheta <= temp->getTheta() <= upTheta){
            CIwSVec2 tempPos = temp->getPosition();
            float dist = sqrt((tempPos.x+Pos.x)*(tempPos.x+Pos.x)+(tempPos.y+Pos.y)*(tempPos.y+Pos.y));
            if (dist<=(size+temp->getSize())) {
                collide_array->push_back(temp);
            }
        }
    }
    return collide_array;
}
 