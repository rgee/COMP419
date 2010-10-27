#ifndef _UNIT_H
#define _UNIT_H

#include "player.h"

class Unit {
    private:
        float hp, speed, x, y, attackRate;
        int uid;
        Player *owner;
        
    public:
        int getId();
        void setId(int uid);
        
        Player *getOwner();
        void setOwner(Player *p);
        
        float getHp();
        void setHp(float f);
        void decrementHp(float f);
        
        virtual void display() = 0;
};

#endif