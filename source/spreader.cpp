#include "spreader.h"

Spreader::Spreader(Player* owner, Game* game, float x, float y)
        : Unit(250.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 7.0f, 5.0f, owner, game){
    spriteSize = 256;
    numFrames = 11;
    curFrame = 0;
    scale = 0.25f;
    maxSpread = 3;
    sinceLastSpread = 0;
	spreadDelay = 12;
    setPosition(x, y);
	worldRad = game->getWorldRadius();
	texture_names.push_back(IwHashString("spreader_sprite_sheet"));
    srand(time(NULL));

    maxIcingCount = 0;
    for(int i = 1; i <= maxSpread; i++) {
        maxIcingCount += (2*PI) / (PI/4.0/(float)i);
    }
    
    currentRadius = 1;
    currentJump = PI/4.0/currentRadius;
    radiusMaxIcing = (2*PI) / (PI/4.0/currentRadius);
    icingThisRadius = 0;
}

Spreader::Spreader(const Spreader& newSpreader) : Unit(newSpreader) {
	spreadDelay = 13;
	worldRad = game->getWorldRadius();
}

bool Spreader::shouldAIUpdate() {
    return false;
}

bool Spreader::update(std::list<Unit*>::iterator itr){
    // Create icing in a winding out counter-clockwise pattern.
    if(icingMap.size() < maxIcingCount && sinceLastSpread % spreadDelay == 0) {

        ++spreadDelay;
        sinceLastSpread = 0;
        
        if(icingThisRadius == radiusMaxIcing) {
            ++currentRadius;
            icingThisRadius = 0;
            currentJump = PI/4.0f/currentRadius;
            radiusMaxIcing = (2*PI) / (PI/4.0f/currentRadius);
        }

        float actualRadius = currentRadius * 20.0f;
        float spreadTheta = fmod(currentJump * icingThisRadius, 2*PI);
        float xOffset = actualRadius * cos(spreadTheta);
        float yOffset = actualRadius * sin(spreadTheta);
        std::pair<int, float> key = std::make_pair<int, float>(currentRadius, spreadTheta);

            if(!icingMap[key]) {

                // Only add icing to the GAME if it's in the world, so we can still breadcrumb off-world slots.
	            if(isInWorld(CIwFVec2(position.x + xOffset, position.y + yOffset), worldRad.x, worldRad.y)) {
                    game->addIcing(new Icing(CIwFVec2(position.x + xOffset, position.y + yOffset), game, owner));
                }

                icingMap[key] = true;
                ++icingThisRadius;
	        }
    }
	
    ++sinceLastSpread;

	curFrame = (curFrame + 1) % numFrames;
    return true;
}

Spreader::~Spreader() {
    icingMap.clear();
}

unit_type Spreader::getType() {
	return SPREADER;
}

Unit* Spreader::spawnCopy() {
	return new Spreader(*this);
}

IceMap* Spreader::getIcing() {
    return &icingMap;
}



