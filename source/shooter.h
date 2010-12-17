#ifndef _SHOOTER_H
#define _SHOOTER_H

#include "unit.h" 

class Shooter : public Unit {
	public:
		Shooter(Player* owner, Game* game, float x, float y);
		Shooter(const Shooter& newShooter);
		~Shooter(){ s3eDebugOutputString("destroying shooter"); };

		virtual bool update(std::list<Unit*>::iterator itr);

		virtual unit_type getType();
	
		virtual Unit* spawnCopy();
        
    
        std::map<unit_type, int> statAttacks;
    
        virtual void attack();
        virtual int getDamage(Unit* unit);
        virtual bool shouldAIUpdate();
	
	private:
	
		int projectileCount;

};

#endif
