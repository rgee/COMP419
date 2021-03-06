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
        
        virtual void attack();

        virtual bool update(std::list<Unit*>::iterator itr);

		virtual unit_type getType();
		virtual Unit* spawnCopy();
    

};

#endif
