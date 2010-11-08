#ifndef _MUNCHER_H
#define _MUNCHER_H

#include "unit.h"

class Muncher : public Unit {
	
	public:
	
		Muncher(Player* owner, Game* game, CIwVec2 position);
	
		~Muncher() {};

		virtual char* getTextureName();
		virtual bool update();
		virtual void display();
};

#endif