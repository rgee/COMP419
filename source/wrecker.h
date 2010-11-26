#ifndef _WRECKER_H
#define _WRECKER_H

#include "unit.h"

class Wrecker : public Unit {
	public:
		Wrecker(Player* owner, Game* game, float x, float y);
		Wrecker(const Wrecker& wrecker);
		~Wrecker(){};

		virtual bool update();
        virtual const char* getTextureName();
		virtual unit_type getType();
	
		virtual Unit* spawnCopy();

};

#endif