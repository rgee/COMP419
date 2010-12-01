#ifndef _THROWER_H
#define _THROWER_H

#include "unit.h"

class Thrower : public Unit {
	public:
		Thrower(Player* owner, Game* game, float x, float y);
		Thrower(const Thrower& newThrower);
		~Thrower(){};

		virtual bool update();
		virtual void display();
		virtual unit_type getType();
	
		virtual Unit* spawnCopy();
    
        std::map<unit_type, int> statAttacks;
    
        virtual void attack();
        virtual void receiveDamage(float amount, Unit *attacker); 
        virtual int getDammage(Unit* unit);
    
         

};

#endif
