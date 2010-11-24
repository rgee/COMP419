#ifndef _WRECKER_H
#define _WRECKER_H

#include "unit.h"

class Wrecker : public Unit {
	public:
		Wrecker(Player* owner, Game* game, CIwFVec2 position);
		~Wrecker(){};

		virtual bool update();
		virtual void display();
        virtual char* getTextureName();
};

#endif