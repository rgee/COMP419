#include "player.h"

Player::Player(CIwColour& col) {
	
    color = col;
    colors = (CIwColour*) malloc(4*sizeof(CIwColour));
    colors[0] = colors[1] = colors[2] = colors[3] = col;
}

Player::~Player(){
    free(colors);
}

CIwColour& Player::getColor() {
	return color;
}

CIwColour *Player::getColors(){
    return colors;
}

void Player::setLeader(Leader* _leader) {
	leader = _leader;
}

Leader* Player::getLeader() {
	return leader;
}
