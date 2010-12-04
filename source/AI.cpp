#include "AI.h"
 /* 
Unit* AI::detectEnemy(std::list<Unit*>::iterator unit_itr) {
    std::list<Unit*>* units = game->getUnits();
    CIwFVec2 position = (*unit_itr)->getPosition() + (*unit_itr)->getVelocity();
    CIwFVec2 otherPos = CIwFVec2::g_Zero;
    
    float sq_dist = 0;
    float closest_distance = SQ((*unit_itr)->getSight());
    float max_dist = closest_distance;
    Unit* closest = (*unit_itr)->getTarget();
    
    / **
     * In order to avoid brute-force distance calculations, we take advantage of
     * the fact that the units are sorted by their theta values. We begin our distance
     * checking at the given unit's position in the sorted container, then at each
     * step, check the unit with the next nearest theta, and see if it's close enough.
     * 
     * We stop once we've reached a unit that is completely outside the sight range,
     * We do the same thing in both directions to find the closest unit.
     * /
    std::list<Unit*>::iterator incr_theta_itr = unit_itr;
    std::list<Unit*>::iterator decr_theta_itr = unit_itr;
    while(incr_theta_itr != units->end() && sq_dist <= max_dist) {
        // Look up theta, which means we're moving to the BACK of the container
        if(&(*incr_theta_itr)->getOwner() != &(*unit_itr)->getOwner()) {
            otherPos = (*incr_theta_itr)->getPosition();
            sq_dist = SQ(position.x - otherPos.x) + SQ(position.y - otherPos.y);
            
            if(sq_dist < closest_distance && (*incr_theta_itr)->getHp() > 0) {
                closest_distance = sq_dist;
                closest = *(incr_theta_itr);
			}
        }
        ++incr_theta_itr;
    }

    // Must reset the distance here since we're switching directions.
    sq_dist = 0.0f;
    while(decr_theta_itr != units->begin() && sq_dist <= max_dist) {
        // Look down theta, which means we're moving to the FRONT of the container. 
        if(&(*decr_theta_itr)->getOwner() != &(*unit_itr)->getOwner()) {
            otherPos = (*decr_theta_itr)->getPosition();
            sq_dist = SQ(position.x - otherPos.x) + SQ(position.y - otherPos.y);
            
            if(sq_dist < closest_distance && (*decr_theta_itr)->getHp() > 0) {
                closest_distance = sq_dist;
                closest = *(decr_theta_itr);
			}
        }
        --decr_theta_itr;
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
		
		if((*itr) != unit && (*itr)->getHp() >= 0) {
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
*/
