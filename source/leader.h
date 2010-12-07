#ifndef _LEADER_H
#define _LEADER_H

#include "unit.h"
#include "IwRandom.h"

class Leader : public Unit {
	private:
		short framesUntilUpdate;
	public:
		Leader(Player* owner, Game* game, float x, float y);
		~Leader(){};

		virtual bool update(std::list<Unit*>::iterator itr);
		virtual unit_type getType();
		virtual float getAngle();
};

#endif
