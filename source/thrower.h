#ifndef _THROWER_H
#define _THROWER_H

#include "unit.h"

class Thrower : public Unit {
	public:
		Thrower(Player* owner, Game* game, float x, float y);
		Thrower(const Thrower& newThrower);
		~Thrower(){};

		virtual bool update();
		virtual unit_type getType();
	
		virtual Unit* spawnCopy();
    
        virtual const char* getTextureName();
};

#endif
