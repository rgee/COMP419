#ifndef _AI_H 
#define _AI_H

#include <math.h>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>

class AI;

#include "util.h"
#include "unit.h"


class AI{
    private:
        CIwFVec2 worldRad;
        Game* game;

		
        void path(Unit* unit);
        
        bool attack(Unit* unit);

		/**
		 * Detects the nearest enemy unit to the specified unit.
		 *
		 * @param unit The unit seeking an enemy.
		 * @return The nearest enemy.
		 */
        Unit* detectEnemy(Unit* unit);
        
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

		/**
		 * Checks whether the specified position is on the world or not.
		 *
		 * @param pos The position to check.
		 * @return True if the position is on the world, false otherwise.
		 */
		bool onWorld(const CIwFVec2& pos) const;

    public: 
    
        AI(Game* game);
    
		/**
		 * Update a unit's AI.
		 *
		 * @param unit The unit to update.
		 */
        void updateAI(Unit* unit);
        
};

#endif
