#ifndef _MUNCHER_H
#define _MUNCHER_H

#include "unit.h"
#include <math.h>

class Muncher : public Unit {

	public:

		Muncher(Player* owner, Game* game, float x, float y);

		~Muncher() {};

		virtual const char* getTextureName();
		virtual bool update();
        virtual void attack();
        virtual void receiveDamage(float amount, Unit *attacker); 
        virtual int getDammage(Unit* unit);
};

#endif