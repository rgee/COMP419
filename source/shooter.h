#ifndef _SHOOTER_H
#define _SHOOTER_H

#include "unit.h"

class Shooter : public Unit {
	public:
		Shooter(Player* owner, Game* game, float x, float y);
		Shooter(const Shooter& newShooter);
		~Shooter(){};

		virtual bool update();
		virtual const char* getTextureName();
		virtual unit_type getType();
	
		virtual Unit* spawnCopy();

};

#endif