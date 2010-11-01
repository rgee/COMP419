#ifndef _STATE_MANAGER_H
#define _STATE_MANAGER_H

#include "IwArray.h"
class GameState;

class StateManager{
	public:
		StateManager();

		void tick();
		void push_state(GameState& newState);
		GameState* pop_state();
		GameState* peek_state() const;
	private:
		CIwArray<GameState*> states;
};

#endif