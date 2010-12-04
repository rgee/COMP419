#ifndef _LEADER_H
#define _LEADER_H

#include "unit.h"
#include "IwRandom.h"

class Leader : public Unit {
	public:
		Leader(Player* owner, Game* game, float x, float y);
		~Leader(){};

		virtual bool update(std::list<Unit*>::iterator itr);
		virtual const char* getTextureName();
		virtual unit_type getType();
};

#endif