#ifndef _UNIT_H
#define _UNIT_H


#include "game.h"
#include "player.h"
#include "Iw2D.h"

#include "IwGeomVec2.h"

class Unit {
    protected:
		/* Preliminary stats. Subject to change. */
	    float hp;
		float cost;
		float attack;
		float speed;
		float munch_speed;
		float range;
		float sight;
		float spread_speed;
		float spread_radius;

		float r; 
		float theta;

		Player *owner;
		Game* game;
		CIwSVec2 position;
		int uid;
		char* texture_name;
        
    public:
		Unit(float hp, float cost, float attack, float speed, 
				float munch_speed, float range, float sight,
				float spread_speed, float spread_radius, Player* owner,
				Game* game, CIwVec2 position);

		virtual ~Unit() {};

		void setPosition(int32 x, int32 y);
		void setPosition(const CIwVec2& position);
    
		int getId();
		void setId(int uuid);

		char* get_tex_name();
        
		Player& getOwner();
		void setOwner(Player& p);
        
		float getHp();
		void setHp(float f);
		void decrementHp(float f);
		
		float getR();
		float getTheta();
	
		void setR(float x);
		void setTheta(float y);

		/* Units are going to keep track of their location in terms of r, theta, but
		   the following methods preserve distance, so calling increaseX(5.0f) might
		   change theta by more or less than 5. Additionally, it will wrap around
		   as appropriate.
		 */
		void increaseX(float x);
		void increaseY(float y);
		float getX();
		float getY();
		virtual bool update() = 0;
		virtual void display() = 0;
	
		/**
		 Render the unit to the screen. Units are responsible for orienting themselves
		 properly on screen. 
		 
		 @param centerX horizontal screen coordinate of the point this unit is centered at
		 @param centerY vertical screen coordinate of the point this unit is centered a
		 @param rotAngle angle to rotate the rendering by so that, as the world is rotated, the unit's
				orientation adjusts appropriately
		 @param frameNumber the current frame that we're rendering. Useful for animating sprites.
		 */
        //virtual void display(int centerX, int centerY, iwangle rotAngle, int frameNumber) = 0;
		//virtual bool update() = 0;
	
};

#endif
