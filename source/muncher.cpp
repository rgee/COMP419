#include "muncher.h"



bool Muncher::update(){
	return true;
}

void Muncher::display(){

}
Muncher::Muncher(Player* owner, Game* game, CIwVec2 position)

	: Unit(100.0f, 50.0f, 10.0f, 15.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game, position)
{
}