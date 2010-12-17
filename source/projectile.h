#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "unit.h"

class Projectile : public Unit {
	
	public:
		
		Projectile(Player* owner, Game* game, float x, float y, CIwFVec2 velocity, Unit* _target);
	
		virtual bool update(std::list<Unit*>::iterator itr);
	
		virtual unit_type getType();

	private:
		
		CIwFVec2 worldRad;
		
		float minTargetDist;
	
};

#endif
