#ifndef _UNIT_H
#define _UNIT_H

class Unit;

#include "worldobject.h"
#include "game.h"
#include "player.h"
#include "player.h"

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
