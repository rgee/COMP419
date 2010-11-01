#ifndef _UNIT_H
#define _UNIT_H


#include "game.h"
#include "player.h"
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

		float row; 
		float col;
        Player *owner;
        int uuid;
		Game* game;
		CIwVec2 position;
        
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
        
		Player& getOwner();
		void setOwner(Player& p);
        
		float getHp();
		void setHp(float f);
		void decrementHp(float f);
	
		void setRow(float x);
		float getRow();
	
		void setCol(float y);
		float getCol();

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
};

#endif
