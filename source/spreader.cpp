#include "spreader.h"

Spreader::Spreader(Player* owner, Game* game, CIwFVec2 position)
	: Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 300.0f, owner, game, position)
{

}

void Spreader::display(){

}

bool Spreader::update(){
	return true;
}

const char* Spreader::getTextureName(){
    return "muncher_sprite_sheet";
}
