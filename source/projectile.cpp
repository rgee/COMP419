#include "projectile.h"

Projectile::Projectile(Player* owner, Game* game, float x, float y, CIwFVec2 _velocity)
: Unit(100.0f, 50.0f, 10.0f, 20.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 8;
	curFrame = 0;
    scale = 0.1f;
    setPosition(x, y);
	velocity = _velocity;
	texture_names.push_back(IwHashString("projectile_sprite_sheet"));
	worldRad = game->getWorldRadius();
}

bool Projectile::update(std::list<Unit*>::iterator itr) {
    curFrame = (curFrame + 1) % numFrames;
	setPosition(position + speed*velocity);
	float r = getR();
	
	if (r <= worldRad.x || r >= worldRad.y) {
		hp = -1;
		s3eDebugOutputString("dead!");
	}
	
	
	return true;
}

unit_type Projectile::getType() {
	return PROJECTILE;
}
