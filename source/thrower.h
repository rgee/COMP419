#ifndef _THROWER_H
#define _THROWER_H

#include "unit.h"

class Thrower : public Unit {
    private:
        int framesUntilUpdate;
	public:
		Thrower(Player* owner, Game* game, float x, float y);
		Thrower(const Thrower& newThrower);
		~Thrower(){};


        std::map<unit_type, int> statAttacks;
        
        virtual void attack();
        virtual int getDamage(Unit* unit);
        virtual const char* getTextureName();
        virtual bool update(std::list<Unit*>::iterator itr);
		virtual unit_type getType();
		virtual Unit* spawnCopy();
    

};

#endif
