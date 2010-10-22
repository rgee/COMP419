class Game {
    private:
        Player players[];
        int numPlayers;
        
        GridCell cells[][]; // Format: cell[row][col]
        int rows, cols;
        
        CIwArray<Unit> *units;
                
    public:
        Game(int numPlayers, int numRows, int numCols);
        
        void addUnit(Unit *u){
            u->id = units->size();
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
}