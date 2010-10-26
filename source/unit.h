#include "player.h"

class Unit {
    private:
        float hp, speed, x, y, attackRate;
        int id;
        Player *owner;
        
    public:
        int getId();
        void setId(int id);
        
        Player *getOwner();
        void setOwner(Player *p);
        
        float getHp();
        void setHp(float f);
        void decrementHp(float f);
        
        virtual void display() = 0;
}