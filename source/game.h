#ifndef _GAME_H
#define _GAME_H

#include "IwArray.h"

class Game;
class Unit;

#include <map>
#include <set>
#include <list>
#include <deque>
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
        
        //CIwArray<Unit*> units;

        std::list<Unit*> units;

		// Queue of units we're set to 
		std::list<Unit*> unitBuffer;

		CIwResGroup* resources;
		
		UnitBucket unitBucket;
	
		long timesteps;
	
		void initRenderState();
	                    
    public:
	
        Game(int numPlayers);
		~Game();
        
        void addUnit(Unit *u);
		std::list<Unit*>* getUnits();
        	
		void tick();
	
		void render();
		
		long getTimesteps();

};

#endif