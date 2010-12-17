#ifndef _PLAYER_H
#define _PLAYER_H

class Leader;
class Unit;

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

class Game;

class RemotePlayer : public Player {
    protected:
        Game* game;
    public:
        RemotePlayer(CIwColour& col) : Player(col){}
        virtual bool connect() = 0;
        virtual void sendUpdate(Unit *) = 0;
        virtual void applyUpdates() = 0;
        virtual void sendSync() = 0;
        void setGame(Game *g){ game = g; }
};

#endif
