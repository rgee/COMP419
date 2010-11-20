#ifndef _UNIT_H
#define _UNIT_H

#include "IwGx.h"
#include "IwGeom.h"
#include "game.h"
#include "player.h"

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
	
		//info for sprite animation
		int spriteSize;
		int numFrames;
		int curFrame;
	
		/**
		Utility method that subclasses will use to render their sprites. Assumes that 
		current material has already been set to the sprite image.
		 
		@param frameNumber which frame of the sprite sheet to display (indexed from 0)
		@param angle angle to rotate the sprite by
		@param scaleFactor factor to scale the sprite by
		*/
		void renderSprite(int frameNumber, float angle, float scaleFactor);

        
    public:
	
		Unit(float hp, float cost, float attack, float speed, 
				float munch_speed, float range, float sight,
				float spread_speed, float spread_radius, Player* owner,
				Game* game, CIwVec2 position);

		Unit(const Unit& newUnit);

		virtual ~Unit() {};

		void setPosition(int32 x, int32 y);
		void setPosition(const CIwVec2& position);
    
		int getId();
		void setId(int uuid);
        
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
	
		virtual char* getTextureName() = 0;
		virtual bool update() = 0;
		virtual void display() = 0;
};

#endif
