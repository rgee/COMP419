#ifndef _UNIT_H
#define _UNIT_H

class Unit;

#include "worldobject.h"
#include "game.h"
#include "player.h"
#include "player.h"

/**
This lets us quickly determine a unit's type at run time.
*/
enum unit_type {
	MUNCHER, SHOOTER, SPREADER, WRECKER, THROWER
};

class Unit : public WorldObject {
    
	protected:    
		/* Preliminary stats. Subject to change. */
	    float hp;
		float cost;
		float attackDamage;
		float speed;
		float munch_speed;
		float range;
		float sight;
		float spread_speed;
		float spread_radius;
        float scale;

		Player *owner;
		CIwFVec2 velocity;
		int uid;
	
		//info for sprite animation
		int spriteSize;
		int numFrames;
		int curFrame;
	
		// The unit this unit is attacking.
		Unit *attackTarget;

		// The unit this unit is pursuing.
		Unit *pursueTarget;
        
    public:
	
		Unit(float hp, float cost, float attack, float speed, 
				float munch_speed, float range, float sight,
				float spread_speed, float spread_radius, Player* owner,
				Game* game);

		Unit(const Unit& newUnit);

		virtual ~Unit() {};
    
		bool operator<(const Unit& u) const;
	
		virtual unit_type getType() = 0;

        void setVelocity(const CIwFVec2& velocity);
        void setVelocity(float xv, float yv);
    
        CIwFVec2 getVelocity();

    
		float getSpeed(); 
		float getRange();
        float getSize();
		int getId();
		void setId(int uuid);
        
		Player& getOwner();
		void setOwner(Player* p);
			
		Unit* getAttacking();
		void setAttacking(Unit* unit);
		
		Unit* getPursuing();
		void setPursuing(Unit* unit);
	
		bool attacking();
		bool pursuing();
        
		float getHp();
		void setHp(float f);
		void decrementHp(float f);

		/* IGNORE THE FOLLOWING.  I already updated set position to change theta and r
		 and vice versa so use which ever coordinate system works best for you cause
		 their are times where either works.
		 
		   Units are going to keep track of their location in terms of r, theta, but
		   the following methods preserve distance, so calling increaseX(5.0f) might
		   change theta by more or less than 5. Additionally, it will wrap around
		   as appropriate.
		 */
		void increaseX(float x);
		void increaseY(float y);
	

		/*
		 Create a copy of this Unit. This is here so that you can make copies of Units without including
		 their header files - it's a workaround for doing the mirror opponent, but could be useful
		 in the future. 
		 */
		virtual Unit* spawnCopy() { return NULL; };
		
		virtual const char* getTextureName() = 0;
	
		virtual bool update() = 0;
	
        virtual void display();
        void displayOnScreen(int x, int y);
		
		void attack();
		void receiveDamage(); 
    
        float getSight();
        float getAngle();
};

#endif
