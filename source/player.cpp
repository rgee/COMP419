#include "player.h"

Player::Player(CIwColour& col) {
    colors = (CIwColour*) malloc(4*sizeof(CIwColour));
    
    setColor(col);
}

Player::~Player(){
    free(colors);
}

void Player::setColor(CIwColour& col){
    color.Set(col.Get());
    colors[0] = colors[1] = colors[2] = colors[3] = color;
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
