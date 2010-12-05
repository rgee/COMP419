#ifndef _AI_H 
#define _AI_H

#include <stdio.h>
#include <math.h>
#include <list>
#include <vector>
#include <iterator>

#include "game.h"
#include "util.h"
#include "unit.h"

/**
* Detects the nearest enemy unit to the specified unit.
*
* @param unit_itr An iteratot to the unit in the sorted unit
*                 data structure.
* @return The nearest enemy.
*/
Unit* detectEnemy(std::list<Unit*>::iterator unit_itr);

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
		
#endif
