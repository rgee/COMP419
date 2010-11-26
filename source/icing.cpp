#include "icing.h"

Icing::Icing(CIwFVec2 position, Game* game) : WorldObject(position, game) { }

Icing::Icing(const Icing& newIcing) : WorldObject(newIcing) { }

void Icing::display() {
	
	renderImageWorldSpace(position, 0.0, .3, 256, game->getRotation(), 0, 1);
}

const char* Icing::getTextureName() {
	return "icing";
}