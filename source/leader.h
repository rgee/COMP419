#ifndef _LEADER_H
#define _LEADER_H

#include "unit.h"
#include "IwRandom.h"

class Leader : public Unit {
	public:
		Leader(Player* owner, Game* game, CIwFVec2 position);
		~Leader(){};

		virtual bool update();
		virtual void display();
		virtual char* getTextureName();
};

#endif