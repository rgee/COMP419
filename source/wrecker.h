#ifndef _WRECKER_H
#define _WRECKER_H

#include "unit.h"
#include <map>

class Wrecker : public Unit {
	public:
        std::map<unit_type, int> statAttacks;
		Wrecker(Player* owner, Game* game, float x, float y);
		Wrecker(const Wrecker& wrecker);
		~Wrecker(){};

		virtual bool update();
        virtual const char* getTextureName();
		virtual unit_type getType();
	
		virtual Unit* spawnCopy();
    
        virtual void attack();
        virtual int getDamage(Unit* unit);

};

#endif
