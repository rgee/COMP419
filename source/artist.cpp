#include "artist.h"

void updateChangeList(CIwArray<GridCell*> changeList) {
    changeList = _changeList;
}

void Artist(Game* _game, UIManager* _ui) : game(_game), ui(_ui) {};

void render() {
    
    for(CIwArray<GridCell*>::iterator gc_it = changeList.begin(); gc_it != changeList; ++gc_it) {
        
        std::set<Unit*> units = gc_it->getUnits();
        
        for(std::set<Unit*>::iterator u_it= units.begin(); u_it != units.end(); ++u_it) {
            u_it->render()
        }
    }
}
