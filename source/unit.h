#ifndef _UNIT_H
#define _UNIT_H

#include "player.h"

class Unit {
    private:
        float hp, speed, x, y, attackRate;
        Player *owner;
        int uuid;
        
    public:
        int getId();
        void setId(int uuid);
        
        Player *getOwner();
        void setOwner(Player *p);
        
        float getHp();
        void setHp(float f);
        void decrementHp(float f);
        
        virtual void display() = 0;
};

#endif