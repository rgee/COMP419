#include "leader.h"

Leader::Leader(Player* owner, Game* game, float x, float y)
		: Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 5.0f, owner, game){
    spriteSize = 256;
    numFrames = 3;
    curFrame = 0;
    scale = 0.25f;
    setPosition(x, y);
}

bool Leader::update(std::list<Unit*>::iterator itr){
	curFrame = IwRandMinMax(0, numFrames-1);
	return true;
}

const char* Leader::getTextureName() {
	return "leader_sprite_sheet";
}

unit_type Leader::getType(){
	return LEADER;
}