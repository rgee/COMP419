class Game {
    private:
        Player players[];
        int numPlayers;
        
        GridCell cells[][]; // Format: cell[row][col]
        int rows, cols;
        
        CIwArray<Unit*> units;
                    
    public:
        Game(int numPlayers, int numRows, int numCols);
        
        void addUnit(Unit *u);

        GridCell * getCell(int row, int col);
        
        CIwArray<Unit> * getUnitsNear(int row, int col, int radius);
        
        int getWidth();
        int getHeight();
}