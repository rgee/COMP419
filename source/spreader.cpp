#include "spreader.h"

Spreader::Spreader(Player* owner, Game* game, float x, float y)
        : Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 300.0f, owner, game){
    spriteSize = 256;
    numFrames = 11;
    curFrame = 0;
    scale = 0.25f;
    framesUntilUpdate = 0;
    setPosition(x, y);
}

Spreader::Spreader(const Spreader& newSpreader) : framesUntilUpdate(0), Unit(newSpreader) { }

bool Spreader::update(){
    if(framesUntilUpdate == 0){
        curFrame = (curFrame + 1) % numFrames;   
        framesUntilUpdate = 2;
    }else{
        --framesUntilUpdate;
    }
    return true;
}

const char* Spreader::getTextureName(){
    return "spreader_sprite_sheet";
}

unit_type Spreader::getType() {
	return SPREADER;
}

Unit* Spreader::spawnCopy() {
	return new Spreader(*this);
}

