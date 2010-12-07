#ifndef _PLAYER_H
#define _PLAYER_H

class Leader;

#include "IwColour.h"

class Player {
	private:
        CIwColour color; 
        CIwColour *colors;
		Leader* leader;
	
	public:
        Player(CIwColour& col);
        ~Player();
		CIwColour& getColor();
        CIwColour* getColors();
		void setLeader(Leader* _leader);
		Leader* getLeader();
};

#endif
