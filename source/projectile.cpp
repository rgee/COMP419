#include "projectile.h"

Projectile::Projectile(Player* owner, Game* game, float x, float y, CIwFVec2 _velocity, Unit* _target)
: Unit(100.0f, 50.0f, 10.0f, 20.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 8;
	curFrame = 0;
    scale = 0.1f;
    setPosition(x, y);
	velocity = _velocity;
	texture_names.push_back(IwHashString("projectile_sprite_sheet"));
	
	target = _target;
	worldRad = game->getWorldRadius();
	minTargetDist = SQ(target->getSize()/2);
}

bool Projectile::update(std::list<Unit*>::iterator itr) {
    curFrame = (curFrame + 1) % numFrames;
	setPosition(position + speed*velocity);
	float r = getR();
	
	/*if (target->getPosition()) {
		
	}*/
	
	if (r <= worldRad.x || r >= worldRad.y) {
		hp = -1;
	}
	
	return true;
}

unit_type Projectile::getType() {
	return PROJECTILE;
}
