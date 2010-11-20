
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
		//Check for collision on tempPos and then attack if true else update.
	}
	else {
		//Detect enemies on same model as collision detection.
		float thetaChange = speed/rad;
		float tempTheta = thetaChange + theta;
		//check for collisions on new pos R,tempTheta then update.
	}
		
}
			
bool AI::Attack(Unit& unit){
	if(!unit.attacking()){
	unit.setAttacking(unit.getPursuing());
	}
	if(unit.attacking() && unit.pursuing()){
		unit.setPursuing(NULL);
	}
	
} 
Unit& AI::Detect_Enemy(Unit& unit){
	//CIwArray<Unit*>* Units = unit.getGame().getUnits();
}
void AI::UpdateAI(Unit& unit){
	
	
}
Unit* CollisionDetection(Unit& unit, CIwArray<Unit*>* Units){}
 