#ifndef _AI_H 
#define _AI_H

#include "game.h"
#include "unit.h"

 
class AI{
	
protected:  
	void Path(Unit& unit);
	bool Attack(Unit& unit);
	Unit* Detect_Enemy(Unit& unit, CIwArray<Unit*>* Units);
    CIwArray<Unit*>* CollisionDetection(Unit& unit, CIwArray<Unit*>* Units);
public: 
	AI();
	virtual ~AI();
	void UpdateAI(Unit& unit);
	
	
	
};
#endif