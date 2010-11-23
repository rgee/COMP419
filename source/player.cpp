#include "player.h"

Player::Player(CIwColour _color) : color(_color) { }

CIwColour Player::getColor() {
	return color;
}