#include "icing.h"
#include "game.h"

Icing::Icing(const CIwFVec2 position, Game* game, Player* owner) : owner(owner), scale(0.02f), finalScale(.12f), WorldObject(position, game)  { 
	angle = TO_RADIANS(IwRandMinMax(0, 360));
}

Icing::Icing(const Icing& newIcing) : owner(newIcing.owner), scale(0.02f), finalScale(.12f), WorldObject(newIcing) { }

Player* Icing::getOwner() {
	return owner;
}

void Icing::display() {
	
	CIwColour ownerCol = owner->getColor();
	
	CIwColour* colors = (CIwColour*)malloc(sizeof(CIwColour)*4);
	
	colors[0] = ownerCol;
	colors[1] = ownerCol;
	colors[2] = ownerCol;
	colors[3] = ownerCol;
	
	IwGxSetColStream(colors, 4);
	
	scale = scale < finalScale ? scale + .04 : scale;
	
	renderImageWorldSpace(position, angle, scale, 256, game->getRotation(), 0, 1);
	
	delete colors;
}

const char* Icing::getTextureName() {
	return "icing";
}