#ifndef _THROWER_H
#define _THROWER_H

#include "unit.h"

class Thrower : public Unit {
	public:
		Thrower(Player* owner, Game* game, CIwFVec2 position);
		~Thrower(){};

		virtual bool update();
		virtual void display();

};

#endif