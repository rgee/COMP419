#ifndef _ARTIST_H
#define _ARTIST_H

#include <set>
#include "IwUtil.h"
#include "Iw2D.h"
#include "game.h"
#include "unit.h"
#include "gridcell.h"

//forward declare to stop the compiler from complaining
class UIManager;

class Artist {

    private:
    
        Game* game;
        UIManager* ui;
        CIwArray<GridCell*> changeList;
    
    public:
        
        Artist(Game* _game, UIManager* _ui);
        
        /**
        Alert the Artist object of all cells that changed, and hence
        need to be re-rendered.
        
        @param changeList the list of cells that have changed
        */
        void updateChangeList(CIwArray<GridCell*> _changeList);
        
        /**
        Render the entire game world.
        */
        void render();
};

#endif