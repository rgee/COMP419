#ifndef _UNIT_H
#define _UNIT_H

class Unit;

#include "worldobject.h"
#include "game.h"
#include "player.h"
#include "player.h"
#include "IwDebugPrim.h"
#include <string>
#include "AI.h"


/**
This lets us quickly determine a unit's type at run time.
*/
enum unit_type {
	MUNCHER, SHOOTER, SPREADER, WRECKER, THROWER, LEADER
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
        bool localPlayedOwnsThis;
    
		CIwFVec2 velocity;
		int uid;
		
		//info for sprite animation
		int spriteSize;
		int numFrames;
		int curFrame;
            
        std::string unitType;
	
		Unit *target;
        
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
        bool isLocal();
			
		Unit* getTarget();
		void setTarget(Unit* unit);
		
        bool hasTarget();
        
		float getHp();
		void setHp(float f);

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
		
		virtual void attack();
        void receiveDamage(float amount, Unit* attacker); 
        virtual int getDamage(Unit* unit);
        
    
        float getSight();
        float getAngle();
    
        float distToTarget();
};

#endif
