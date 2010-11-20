#ifndef _AI_H 
#define _AI_H

#include "game.h"
#include "unit.h"

 
class AI{
	
protected:  
	void Path(Unit& unit);
	bool Attack(Unit& unit);
	Unit* Detect_Enemy(Unit& unit, std::list<Unit*>* Units);
    std::list<Unit*>* CollisionDetection(Unit& unit, std::list<Unit*>* Units);
public: 
	AI();
	void UpdateAI(Unit& unit);
	
	
	
};
#endif