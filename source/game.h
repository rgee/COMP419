#ifndef _GAME_H
#define _GAME_H

#include "IwArray.h"

class Game;
class Unit;

#include <map>
#include <set>
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
        
        CIwArray<Unit*> units;

		CIwResGroup* resources;
		
		UnitBucket unitBucket;
	
		long timesteps;
	
		void initRenderState();
	                    
    public:
	
        Game(int numPlayers);
		~Game();
        
        void addUnit(Unit *u);
		CIwArray<Unit*>* getUnits();
        	
		void tick();
	
		void render();
		
		long getTimesteps();

};

#endif