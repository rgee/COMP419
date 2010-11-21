#ifndef _GAME_H
#define _GAME_H

#include <map>
#include <set>
#include <list>
#include <deque>

#include "string.h"
#include "IwResManager.h"
#include "IwResGroup.h"
#include "IwManagedList.h"
#include "IwGx.h"
#include "IwArray.h"

class Game;

#include "player.h"
#include "unit.h"

#include "AI.h"


typedef std::map<char*, std::set<Unit*>* > UnitBucket;

class Game {
	
    private:
	
        CIwArray<Player*> players;
        int numPlayers;

		AI *ai;

        
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
    


        AI *getAI();


};

#endif