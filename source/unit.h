#ifndef _UNIT_H
#define _UNIT_H

#include "player.h"
#include "IwGeomCore.h"

class Unit {
	
    protected:
	
        float hp, speed, r, theta, attackRate;
        int uid;
        Player *owner;
        
    public:
	
		Unit(float r, float theta);
	
        int getId();
        void setId(int uid);
        Player *getOwner();
        void setOwner(Player *p);
        
        float getHp();
        void setHp(float f);
        void decrementHp(float f);
        
		float getR();
		float getTheta();
	
		/**
		 Render the unit to the screen. Units are responsible for orienting themselves
		 properly on screen. 
		 
		 @param centerX horizontal screen coordinate of the point this unit is centered at
		 @param centerY vertical screen coordinate of the point this unit is centered a
		 @param rotAngle angle to rotate the rendering by so that, as the world is rotated, the unit's
				orientation adjusts appropriately
		 */
        virtual void display(int centerX, int centerY, iwangle rotAngle) = 0;
};

#endif