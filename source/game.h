#ifndef _GAME_H
#define _GAME_H

#include "IwArray.h"

class Game;
class Unit;
class AI;

#include <map>
#include <set>
#include <list>
#include <deque>
#include "AI.h"
#include "string.h"
#include "IwResManager.h"
#include "IwResGroup.h"
#include "IwManagedList.h"
#include "IwGx.h"
#include "player.h"


typedef std::map<char*, std::set<Unit*>* > UnitBucket;

class Game {
	
    private:
	
        CIwArray<Player*> players;
        int numPlayers;
		
        //Must solve AI type error on line bellow.  Think it is an include/preconstruction issue.  Until this is solved
        //I see no way to run AI any suggestions would be appreciated.
        //AI ai; 
        
        //CIwArray<Unit*> units;

        std::list<Unit*> units;
        int numUnits;

		// Queue of units we're set to 
		std::list<Unit*> unitBuffer;

		CIwResGroup* sprites;
		CIwResGroup* game;
		
		UnitBucket unitBucket;
	
		long timesteps;

		float innerRadius;
		float outerRadius;
	
		void initRenderState();
	
		void render();
	
		void renderSprites(float worldRot);
	
		void renderWorld(float worldRot);
	
		void renderUI();
	                    
    public:
	
        Game(int numPlayers);
		~Game();
        
        void addUnit(Unit *u);
		std::list<Unit*>* getUnits();

		/**
		 * Gets the inner and outer radii of the world donut.
		 *
		 * Returns a CIwFVec2 where the x coord is the inner radius
		 * and the y coord is the outer radius.
		 */
		CIwFVec2 getWorldRadius();
        	
		void tick();
			
		long getTimesteps();
    
        //AI getAI();

};

#endif