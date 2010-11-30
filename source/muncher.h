#ifndef _MUNCHER_H
#define _MUNCHER_H

class Muncher;

#include "unit.h"

class Muncher : public Unit {

	public:

		Muncher(Player* owner, Game* game, float x, float y);

		Muncher(const Muncher& newMuncher);
	
		~Muncher() {};

		virtual const char* getTextureName();
		virtual bool update();

        virtual void attack();
        virtual void receiveDamage(float amount, Unit *attacker); 
        virtual int getDammage(Unit* unit);

		virtual unit_type getType();
	
		virtual Unit* spawnCopy();

};

#endif