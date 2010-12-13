#include "spreader.h"

Spreader::Spreader(Player* owner, Game* game, float x, float y)
        : Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 5.0f, owner, game){
    spriteSize = 256;
    numFrames = 11;
    curFrame = 0;
    scale = 0.25f;
    amountSpread = 1;
	spreadDelay = 64;
    setPosition(x, y);
	worldRad = game->getWorldRadius();
	texture_names.push_back(IwHashString("spreader_sprite_sheet"));
}

Spreader::Spreader(const Spreader& newSpreader) : Unit(newSpreader) {
	amountSpread = 1;
	spreadDelay = 64;
	worldRad = game->getWorldRadius();
}

bool Spreader::shouldAIUpdate() {
    return false;
}

bool Spreader::update(std::list<Unit*>::iterator itr){
	
	//This is just using magic numbers right now - we need to discuss
	//how to interpret the units stats/do some refactoring.

    int prev_delay = spreadDelay;
    ++spreadDelay;
	// Take twice as long each time, x & (x + 1) will be true iff x+1 is a power of 2
	if(((prev_delay & (spreadDelay)) == 0) && spreadDelay >= 128) {
		
		//spread 3 layers of icing
		if(amountSpread < 4) {
			
			float radius = amountSpread*20.0f;
			float thetaJump = PI/4.0/(float)amountSpread;
			
			for (double spreadTheta = 0.0; spreadTheta < 2*PI; spreadTheta += thetaJump) {
				
				float xIncr = radius * cos(spreadTheta);
				float yIncr = radius * sin(spreadTheta);
				
				if(isInWorld(CIwFVec2(position.x + xIncr, position.y + yIncr), worldRad.x, worldRad.y)) {
					game->addIcing(new Icing(CIwFVec2(position.x + xIncr, position.y + yIncr), game, owner));
				}
			}
			
			amountSpread++;
		}
	}
	
	curFrame = (curFrame + 1) % numFrames;
    return true;
}

unit_type Spreader::getType() {
	return SPREADER;
}

Unit* Spreader::spawnCopy() {
	return new Spreader(*this);
}




