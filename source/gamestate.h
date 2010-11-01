#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include "artist.h"

#include "statemanager.h"

class GameState {
	protected:
		// Artist object used for rendering
		Artist* artist;

		// The state manager that manages this object.
		StateManager* manager;
	public:
		GameState(Artist* artist, StateManager* manager);


		// Resources should be obtained and loaded in ctor
		// and released and unloaded in the dtor
		virtual ~GameState() {};

		// Respond to input
		virtual bool handleInput() = 0;

		// Update game state
		virtual bool update() = 0;

		// Display this state
		virtual void render() = 0;
};

#endif