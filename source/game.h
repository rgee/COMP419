#include <stdio.h>
#include "IwArray.h"
#include "player.h"
#include "gridcell.h"
#include "unit.h"

class Game {
    private:
        CIwArray<Player> players;
        int numPlayers;
        
        GridCell* cells; // Format: cell[row][col]
        int rows, cols;
        
        CIwArray<Unit> *units;
                
    public:
        Game(int numPlayers, int numRows, int numCols);
        
        void addUnit(Unit *u){
            u->setId(units->size());
            units->push_back(u);
        }
        
        GridCell * getCell(int row, int col){
            return cells[row][col];
        }
        
        // The below functions are for convenience only: they could all be
        // simulated by using getCell.
        void setCellOwner(Player player, int row, int col);
        Player * getCellOwner(int row, int col);
        
        CIwArray<Unit> * getUnitsIn(int row, int col);
        CIwArray<Unit> * getUnitsNear(int row, int col, int radius);
        
        
       // We need to consider how drawing is going to work. Depending on our
       // options, it might be most efficient to have any change that would
       // require a redraw to notify some type of Artist object that then
       // just redraws the necessary cells. For example, if there was only
       // one unit on the board and it moved from cell A to cell B, it would
       // redraw both cells A and B.
       //
       // If we don't do it this way then getCell should suffice for all
       // data-accessing purposes.
}