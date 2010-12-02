#include "AI.h"
  
AI::AI(Game* game):game(game){
    worldRad = game->getWorldRadius();
}

/*
 The AI state machine for a Unit
 ===============================
 
 if no target
    get target
 
 if no target
    move
 else if can attack
    attack
 else
    pursue
*/

void AI::updateAI(Unit* unit){
    if(!unit->hasTarget())
        unit->setTarget(detectEnemy(unit));
    
    if(!unit->hasTarget())
        doIdle(unit);
    else if(unit->getRange() >= unit->distToTarget())
        unit->attack();
    else
        doPursue(unit);
}

void AI::doIdle(Unit *unit){
    CIwFVec2 position = unit->getPosition();
	float r = unit->getR();
	float theta = unit->getTheta();
	float speed = unit->getSpeed();
	
	Player *p = game->getLocalPlayer();
	Player *q = &unit->getOwner();
	float targetTheta = (p == q) ? 0 : PI;
	
	int direction = -1;
	float diff = theta - targetTheta; // so theta or theta - PI
	
	if(diff < PI && diff > 0) direction = 1;
    
	float thetaChange = direction * speed / r; 
    float rChange = getRChange(unit);
    
    CIwFVec2 coords(r + rChange, theta + thetaChange);
    polarToXY(coords);
        
    // We want to move along (coords - position) by speed
    coords -= position;
    coords.Normalise();
    coords *= speed;
        
    unit->setPosition(position + coords);
	unit->setVelocity(coords);
}

float AI::getRChange(Unit* unit) {
    CIwFVec2 position = unit->getPosition();
    float unitR = unit->getR();
    
	std::list<Unit*>* units = game->getUnits();
	float rChange = 0.0;
	
    // THIS IS TOO SLOW.
	for (std::list<Unit*>::iterator itr = units->begin(); itr != units->end(); ++itr) {
		
		Unit* otherUnit = *(itr);
		
		if(otherUnit != unit) {
			
			CIwFVec2 otherPos = otherUnit->getPosition();
			float otherR = otherUnit->getR();
			float otherTheta = otherUnit->getTheta();
			float distSquare = abs((otherPos-position).GetLengthSquared());
			
			
			float rDiff = unitR - otherR;
			float dir = rDiff > 0 ? 1.0 : -1.0;
			
			rChange += dir*15000.0/distSquare;
		}
	}
	
	rChange += 5000.0/SQ(worldRad.x - unitR);
	rChange -= 5000.0/SQ(worldRad.y - unitR); 
	
    return rChange;
}

void AI::doPursue(Unit* unit) {
    CIwFVec2 position = unit->getPosition();
    float speed = unit->getSpeed();
    float range = unit->getRange();
    
    Unit *pursuing = unit->getTarget();
    CIwFVec2 old_position = unit->getPosition();
    CIwFVec2 pursuingPos = pursuing->getPosition();
    
    CIwFVec2 pursuitVector = pursuingPos - unit->getPosition();
    pursuitVector.Normalise();
    pursuitVector *= speed;
    polarize(pursuitVector);
    
    float rChange = getRChange(unit);    
    pursuitVector.x += rChange;
    
    polarToXY(pursuitVector);
    pursuitVector.Normalise();
    pursuitVector *= speed;
    
    unit->setPosition(position + pursuitVector);
	unit->setVelocity(pursuitVector);
}



Unit* AI::detectEnemy(Unit* unit){
    std::list<Unit*>* units = game->getUnits();
    CIwFVec2 position = unit->getPosition() + unit->getVelocity();
    CIwFVec2 temp_Pos = CIwFVec2::g_Zero;
    
    float sq_dist = 0.0f;
    float closest_distance = SQ(unit->getSight());
    Unit* closest =  NULL;
    
    // THIS IS TOO SLOW
    
    // Just treat sight as a radius for now and return the closest enemy unit within it.
    for(std::list<Unit*>::iterator itr = units->begin(); itr != units->end(); ++itr) {
        if(&(*itr)->getOwner() != &unit->getOwner()) {
			temp_Pos = (*itr)->getPosition();
			sq_dist = SQ(position.x - temp_Pos.x) + SQ(position.y - temp_Pos.y);
            
            // Check if we've seen a nearer unit. If so, ignore this one and prefer the closer one.
			if(sq_dist < closest_distance && (*itr)->getHp() > 0) {
                closest_distance = sq_dist;
                closest = *(itr);
			}
		}
	}
    
    return closest;
}

// THIS NEEDS TO BE FASTER
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
