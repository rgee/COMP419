#ifndef _PLAYER_H
#define _PLAYER_H

#include "IwColour.h"

class Player {
	private:
        CIwColour color; 
        CIwColour *colors;
	
	public:
        Player(CIwColour& col);
        ~Player();
		CIwColour& getColor();
        CIwColour* getColors();
};

#endif
