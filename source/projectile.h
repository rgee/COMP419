#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "unit.h"

class Projectile : public Unit {
	
	public:
		
		Projectile(Player* owner, float x, float y, float dir);
	
		virtual bool update(std::list<Unit*>::iterator itr);

}