#include "leader.h"

Leader::Leader(Player* owner, Game* game, float x, float y)
		: Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 5.0f, owner, game){
    spriteSize = 256;
    numFrames = 3;
    curFrame = 0;
    scale = 0.5f;
	framesUntilUpdate = 0;
    setPosition(x, y);
	texture_names.push_back(IwHashString("leader_sprite_sheet"));
    
    CIwFVec2 icePos(r, theta);
    icePos.x -= 30;
    polarToXY(icePos);
    Icing* ice = new Icing(icePos, game, owner);
    game->addIcing(ice);
}

bool Leader::update(std::list<Unit*>::iterator itr){
	if (framesUntilUpdate == 0) {
		curFrame = IwRandMinMax(0, numFrames-1);
		framesUntilUpdate = 24;
	} else {
		--framesUntilUpdate;
	}

	return true;
}

unit_type Leader::getType(){
	return LEADER;
}

float Leader::getAngle(){
	return theta - PI/2;
}
