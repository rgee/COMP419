#ifndef _SHOOTER_H
#define _SHOOTER_H

#include "unit.h"

class Shooter : public Unit {
	public:
		Shooter(Player* owner, Game* game, CIwVec2 position);
		~Shooter(){};

		virtual bool update();
		virtual void display();

};

#endif