#ifndef ARTIST_H
#define ARTIST_H

#include <set>
#include "IwUtil.h"
#include "IwGx.h"
#include "IwResManager.h"
#include "game.h"
#include "unit.h"
#include "gridcell.h"
#include "uimanager.h"

class Artist {

    private:
    
        Game* game;
        UIManager* ui;
        CIwArray<GridCell*>* changeList;
		CIwMaterial* worldMaterial;
	
    public:
        
        Artist(Game* _game, UIManager* _ui);
		~Artist();
        
        /**
        Alert the Artist object of all cells that changed, and hence
        need to be re-rendered.
        
        @param changeList the list of cells that have changed
        */
        void updateChangeList(CIwArray<GridCell*>* _changeList);
        
        /**
        Render the entire screen.
		 
		@param frameNumber the number of the current frame - gets passed down to Units' display() methods
        */
        void render(int frameNumber);
};

#endif