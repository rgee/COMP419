#ifndef _UNIT_H
#define _UNIT_H

class Unit;

#include <string>

#include "worldobject.h"
#include "game.h"
#include "player.h"
#include "IwDebugPrim.h"
#include <string>
#include <vector>
#include <math.h>

//range in which we will consider repulsion/attraction for pathing
#define PATH_THETA_RANGE PI
#define THETA_DIFF(X, Y) (min(abs((X)-(Y)), 2*PI - abs((X) - (Y))))
#define REPEL_FACTOR 8000000
#define LEADER_ATTRACTION 1000
#define CIRCLE_SPRING .0015f
#define FORCE_THRESHOLD 12000
#define NAV_ATTRACT_FACTOR 1000
#define NORMAL_FORCE_THRESHOLD 40000


/**
This lets us quickly determine a unit's type at run time.
*/
enum unit_type {
	MUNCHER, SHOOTER, SPREADER, WRECKER, THROWER, LEADER, PROJECTILE
};

/**
Pathing modes that a unit can be in
 
NORMAL: all is well - move toward the enemy leader and do circular pathing
ESCAPE: fell into equilibrium - ignore enemy leader and circular pathing, 
		go to a wall
OBJECTIVE: trying to go somewhere/chase something - ignore enemy leader, 
		   but not circular pathing
*/
enum path_mode {
	NORMAL, ESCAPE, OBJECTIVE
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
    
        float repulsion_factor;
    
		Player *owner;
        bool localPlayedOwnsThis;
    
		CIwFVec2 velocity;
		int uid;
		
		//info for sprite animation
		int spriteSize;
		int numFrames;
		int curFrame;
        
		std::string unitType;

		CIwFVec2 enemyLeaderPos;
	
		CIwFVec2 navTarget;	//a target the unit will move toward when it's stuck
		CIwFVec2 navTargetPolar; //polar navigation target
		path_mode pathMode; //the current pathing mode that we're in
	
		Unit *target;
	
		/** 
		 Calculate a target (the inner or outer wall) for escape pathing
		 @param toLeader vector pointing from this unit to the enemy leader
		 @param the sum of the forces currently acting on this unit
		 */
		void setEscapeTarget(CIwFVec2 toLeader, CIwFVec2 force);

    public:
	
		Unit(float hp, float cost, float attack, float speed, 
				float munch_speed, float range, float sight,
				float spread_speed, float spread_radius, Player* owner,
				Game* game);

		Unit(const Unit& newUnit);

		virtual ~Unit() {};
    	
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
	
		virtual bool update(std::list<Unit*>::iterator itr) = 0;
	
        virtual void display();
        void displayOnScreen(int x, int y);
		
		virtual void attack();
	
        void receiveDamage(float amount, Unit* attacker); 
        virtual int getDamage(Unit* unit);


		// Set the new sprite for this state
		// and move the unit to the correct bucket in
		// the render-ordering structure.
		//
		// We make this a separate function so it can be called
		// from base-class code. We want to do this as little as
		// possible and immediately after knowing we need to. it's
		// an expensive operation.
		virtual void setAttackSprite(){}
		virtual void setIdleSprite(){}
    
        float getSight();
        virtual float getAngle();
    
        float distToTarget();
	
		void path(std::list<Unit*>::iterator itr);
	
		void detectEnemy(std::list<Unit*>::iterator unit_itr);
};

#endif
