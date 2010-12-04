#ifndef _MUNCHER_H
#define _MUNCHER_H

class Muncher;

#include "unit.h"
#include <map>

class Muncher : public Unit {

	public:

		Muncher(Player* owner, Game* game, float x, float y);

		Muncher(const Muncher& newMuncher);
	
		~Muncher() {};
    
        std::map<unit_type, int> statAttacks;

		virtual const char* getTextureName();
		virtual bool update(std::list<Unit*>::iterator itr);
        
        virtual void attack();
        virtual int getDamage(Unit* unit);

		virtual unit_type getType();
	
		virtual Unit* spawnCopy();
};

#endif
