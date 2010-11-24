#ifndef _SHOOTER_H
#define _SHOOTER_H

#include "unit.h"

class Shooter : public Unit {
	public:
		Shooter(Player* owner, Game* game, CIwFVec2 position);
		~Shooter(){};

		virtual bool update();
		virtual void display();
		virtual char* getTextureName();

};

#endif