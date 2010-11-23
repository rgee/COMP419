#ifndef _PLAYER_H
#define _PLAYER_H

#include "IwColour.h"

class Player {
	
	private:
	
		CIwColour color;
	
	public:
	
		Player(CIwColour color);
	
		CIwColour getColor();
	
};

#endif