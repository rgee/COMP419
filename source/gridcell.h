#include <set>
using namespace std;

class GridCell{
    private:
        Player *owner;
        set<*Unit> *units;
        
    public:
        Player *getOwner();
        void    setOwner(Player *p);
        
        void addUnit(Unit *u);
        bool hasUnit(Unit *u);
        set<*Unit> getUnits();
        void removeUnit(Unit *u);
}