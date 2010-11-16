#ifndef _GAME_H
#define _GAME_H

#include "IwArray.h"

class Game;
class Unit;

#include "player.h"
#include "gridcell.h"
#include "IwResManager.h"

class Game {
    private:
        CIwArray<Player*> players;
        int numPlayers;
        
        CIwArray<Unit*> units;

		CIwResGroup* resources;
	
		long timesteps;
                    
    public:
        Game(int numPlayers);
		~Game();
        
        void addUnit(Unit *u);
		CIwArray<Unit*>* getUnits();
        	
		void tick();
		
		long getTimesteps();
};

#endif