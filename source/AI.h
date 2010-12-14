#ifndef _AI_H 
#define _AI_H
 
class AI;

#include "unit.h"

class AI{
    private:
        CIwFVec2 worldRad;
        Game* game;

    public: 
    
        AI(Game* game);
    
        void updateAI(Unit* unit);
        
        void path(Unit* unit);
        
        bool attack(Unit* unit);
        Unit* detectEnemy(Unit* unit, std::list<Unit*>* Units);
        
        std::list<Unit*>* collisionDetection(Unit* unit, std::list<Unit*>* Units);
            
};

#endif