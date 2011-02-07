#ifndef _WRECKER_H
#define _WRECKER_H

#include "unit.h"
#include <map>

class Wrecker : public Unit {
	public:
		Wrecker(Player* owner, Game* game, float x, float y);
		Wrecker(const Wrecker& wrecker);
		~Wrecker(){};

		virtual bool update(std::list<Unit*>::iterator itr);
		virtual unit_type getType();
		virtual Unit* spawnCopy();
        virtual void attack();

		virtual void setAttackSprite();
		virtual void setIdleSprite();
};

#endif
