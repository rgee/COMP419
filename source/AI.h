#ifndef _AI_H 
#define _AI_H
 
class AI;

#include "unit.h"
#include <math.h>
#include <list>
#include <vector>
#include <iterator>

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
        
		/**
		 * Checks for collisions of a given unit with other units in the world.
		 *
		 * WARNING: This function returns a pointer to DYNAMIC MEMORY. It is the
		 * caller's responsibility to deallocate. Please use the collide function
		 * instead.
		 *
		 * @param unit The unit to check against.
		 * @return A list of units that were in collision with the given unit.
		 */
        std::list<Unit*>* collisionDetection(Unit* unit);

		/**
		 * Checks for collisions between a specified unit at the world.
		 *
		 * @param out An OutputIterator (such at std::back_inserter) that will be used
		 *            to fill the container to which it is bound with the results. Can 
		 *            be bound to any container type.
		 * @param unit The unit to collide with the world.
		 */
        template<typename OutputIterator> void collide(OutputIterator out, Unit* unit);
};

#endif