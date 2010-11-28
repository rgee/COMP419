#include "spreader.h"

Spreader::Spreader(Player* owner, Game* game, float x, float y)
        : Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 5.0f, owner, game){
    spriteSize = 256;
    numFrames = 11;
    curFrame = 0;
    scale = 0.25f;
    amountSpread = 1;
	spreadDelay = 0;
    setPosition(x, y);
}

Spreader::Spreader(const Spreader& newSpreader) : Unit(newSpreader) {
	amountSpread = 1;
	spreadDelay = 0;
}

bool Spreader::update(){
	
	//This is just using magic numbers right now - we need to discuss
	//how to interpret the units stats/do some refactoring.
	
	//wait 30 frames, then spread 1 "layer" of icing every 30 frames
	if(spreadDelay%30 == 0 && spreadDelay >= 30) {
		
		//spread 3 layers of icing
		if(amountSpread < 4) {
			
			float radius = amountSpread*20.0f;
			float thetaJump = PI/4.0/(float)amountSpread;
			
			for (double spreadTheta = 0.0; spreadTheta < 2*PI; spreadTheta += thetaJump) {
				
				float xIncr = radius * cos(spreadTheta);
				float yIncr = radius * sin(spreadTheta);
			
				game->addIcing(new Icing(CIwFVec2(position.x + xIncr, position.y + yIncr), game, owner));
			}
			
			amountSpread++;
		}
	}
	
	spreadDelay++;
	curFrame = (curFrame + 1) % numFrames;
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

