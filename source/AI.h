#ifndef _AI_H 
#define _AI_H

class AI;

#include "game.h"
#include "unit.h"
 
class AI{

    public: 
    
        AI();
    
        void updateAI(Unit* unit);
    
        void path(Unit& unit);
    
        bool attack(Unit& unit);
    
        Unit* detectEnemy(Unit& unit, std::list<Unit*>* Units);
    
        std::list<Unit*>* collisionDetection(Unit& unit, std::list<Unit*>* Units);
            
};

#endif