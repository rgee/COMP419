#include "icing.h"
#include "game.h"

Icing::Icing(const CIwFVec2 position, Game* game, Player* owner) : owner(owner), scale(0.02f), finalScale(.12f), WorldObject(position, game)  { 
	angle = TO_RADIANS(IwRandMinMax(0, 360));
	texture_names.push_back(IwHashString("icing"));
}

Icing::Icing(const Icing& newIcing) : owner(newIcing.owner), scale(0.02f), finalScale(.12f), WorldObject(newIcing) {
}

Player* Icing::getOwner() {
	return owner;
}

void Icing::update() {
	scale = scale < finalScale ? scale + .04 : scale;
}

void Icing::display() {
	IwGxSetColStream(owner->getColors(), 4);
	renderImageWorldSpace(position, angle, scale, 256, game->getRotation(), 0, 1, .2f);
}
