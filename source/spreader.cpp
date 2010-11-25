#include "spreader.h"

Spreader::Spreader(Player* owner, Game* game, CIwFVec2 position)
        : Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 300.0f, owner, game, position){
    spriteSize = 256;
    numFrames = 11;
    curFrame = 0;
    scale = 0.25f;
    framesUntilUpdate = 0;
}

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
