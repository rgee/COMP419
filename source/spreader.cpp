#include "spreader.h"

Spreader::Spreader(Player* owner, Game* game, float x, float y)
        : Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 5.0f, owner, game){
    spriteSize = 256;
    numFrames = 11;
    curFrame = 0;
    scale = 0.25f;
    maxSpread = 3;
    sinceLastSpread = 0;
	spreadDelay = 3;
    setPosition(x, y);
	worldRad = game->getWorldRadius();
	texture_names.push_back(IwHashString("spreader_sprite_sheet"));
    srand(time(NULL));

    maxIcingCount = 0;
    for(int i = 1; i <= maxSpread; i++) {
        maxIcingCount += (2*PI) / (PI/4.0/(float)i);
    }

}

Spreader::Spreader(const Spreader& newSpreader) : Unit(newSpreader) {
	spreadDelay = 3;
	worldRad = game->getWorldRadius();
}

bool Spreader::shouldAIUpdate() {
    return false;
}

bool Spreader::update(std::list<Unit*>::iterator itr){

    // If it's been an appropriate amount of time and we haven't filled our space,
    // just sample a random r and theta and see if it's being used already. If not,
    // add that icing. If so, repeat until an empty slot is found.
    //
    // Not slow for a low maxSpread because the likelihood of having to repeat
    // this step never gets very high and occupied check is constant time.
    if(icingMap.size() < maxIcingCount && sinceLastSpread % spreadDelay == 0) {
        bool foundLocation = false;
        while(!foundLocation) {
            float actualRadius = (rand() % maxSpread + 1);

            float radius = actualRadius*20.0f;
            float thetaJump = PI/4.0/actualRadius;
            float spreadTheta = fmod(thetaJump * rand(), 2*PI);

            float xOffset = radius * cos(spreadTheta);
            float yOffset = radius * sin(spreadTheta);
            std::pair<int, float> key = std::make_pair<int, float>(actualRadius, spreadTheta);

            if(isInWorld(CIwFVec2(position.x + xOffset, position.y + yOffset), worldRad.x, worldRad.y) &&
                !icingMap[key]) {

                Icing* ice = new Icing(CIwFVec2(position.x + xOffset, position.y + yOffset), game, owner);
	            game->addIcing(ice);
                icingMap[key] = ice;
                foundLocation = true;
	        }
        }
    }
	++sinceLastSpread;
	curFrame = (curFrame + 1) % numFrames;
    return true;
}

unit_type Spreader::getType() {
	return SPREADER;
}

Unit* Spreader::spawnCopy() {
	return new Spreader(*this);
}

std::map<std::pair<int, float>, Icing*>* Spreader::getIcing() {
    return &icingMap;
}



