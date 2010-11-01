#ifndef _UNIT_H
#define _UNIT_H

#include "player.h"
class Game;


class Unit {
    private:
        float hp, speed, row, col, attackRate, attackRadius;
        Player *owner;
        int uuid;
		Game* game;
        
    public:

    
    int getId();
    void setId(int uuid);
        
    Player *getOwner();
    void setOwner(Player *p);
        
    float getHp();
    void setHp(float f);
    void decrementHp(float f);
	
	void setRow(float x);
	float getRow();
	
	void setCol(float y);
	float getCol();

	/* Units are going to keep track of their location in terms of r, theta, but
	   the following methods preserve distance, so calling increaseX(5.0f) might
	   change theta by more or less than 5. Additionally, it will wrap around
	   as appropriate.
	 */
	void increaseX(float x);
	void increaseY(float y);
	float getX();
	float getY();

	virtual bool update() = 0;
    virtual void display() = 0;
};

#endif
