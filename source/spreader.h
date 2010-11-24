#ifndef _SPREADER_H
#define _SPREADER_H

#include "unit.h"

class Spreader : public Unit {
	public:
		Spreader(Player* owner, Game* game, CIwFVec2 position);
		~Spreader(){};

		virtual bool update();
		virtual void display();

};

#endif