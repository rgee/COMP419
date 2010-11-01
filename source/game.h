#ifndef _GAME_H
#define _GAME_H

#include "IwArray.h"

class Game;
class Artist;
class Unit;

#include "player.h"
#include "gridcell.h"
#include "uimanager.h"

class Game {
    private:
        CIwArray<Player*> players;
        int numPlayers;
        
        GridCell** cells; // Format: cell[row][col]
        int rows, cols;
        
        CIwArray<Unit*> units;

		Artist* artist;
		UIManager* ui_manager;
	
		long timesteps;
                    
    public:
        Game(int numPlayers, int numRows, int numCols);
		~Game();
        
        void addUnit(Unit *u);

        GridCell * getCell(int row, int col);
	
		// These floats ought to be between 0 and 1.
		GridCell * getCell(float r, float c);
        
		/**
		 * This function returns a new CIwArray created on the heap. The caller
		 * is responsible for deleting it.
		 */
        CIwArray<Unit*>* getUnitsNear(int row, int col, int radius);
        
        int getWidth();
        int getHeight();
	
		void tick();
		
		long getTimesteps();
};

#endif