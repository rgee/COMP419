#include "wrecker.h"

Wrecker::Wrecker(Player* owner, Game* game, float x, float y)
	: Unit(350.0f, 100.0f, 40.0f, 3.0f, 5.0f, 60.0f, 200.0f, 0.0f, 0.0f, owner, game)
{
	spriteSize = 256;
	numFrames = 6;
	curFrame = 0;
    scale = 0.2;
    setPosition(x, y);
    
    statAttacks.insert(std::pair<unit_type, int>(MUNCHER,5));
    statAttacks.insert(std::pair<unit_type, int>(WRECKER,20));
    statAttacks.insert(std::pair<unit_type, int>(THROWER,5));
    statAttacks.insert(std::pair<unit_type, int>(SHOOTER,5));
    statAttacks.insert(std::pair<unit_type, int>(SPREADER,5));
    statAttacks.insert(std::pair<unit_type, int>(LEADER,5));

	texture_names.push_back(IwHashString("wrecker_walk_sprite_sheet"));
	texture_names.push_back(IwHashString("wrecker_attack_sprite_sheet"));
}
 
Wrecker::Wrecker(const Wrecker& newWrecker) : Unit(newWrecker) { }

bool Wrecker::update(std::list<Unit*>::iterator itr){
	curFrame = (curFrame + 1) % numFrames;
	path(itr);
	if (target != NULL) attack();
    return true;
}

void Wrecker::setAttackSprite() {
	if(current_texture_index != 1) {
		UnitBucket buckets = *game->getUnitBucket();
		std::set<Unit*>* ourPool = buckets[texture_names[current_texture_index]];
		ourPool->erase(ourPool->find(this));
		buckets[texture_names[1]]->insert(this);
		numFrames = 8;
		current_texture_index = 1;
	}
}

void Wrecker::setIdleSprite() {
	if(current_texture_index != 0) {
		UnitBucket buckets = *game->getUnitBucket();
		std::set<Unit*>* ourPool = buckets[texture_names[current_texture_index]];
		ourPool->erase(ourPool->find(this));
		buckets[texture_names[0]]->insert(this);
		numFrames = 6;
		current_texture_index = 0;
	}
}

unit_type Wrecker::getType() {
	return WRECKER;
}

Unit* Wrecker::spawnCopy() {
	return new Wrecker(*this);
}

void Wrecker::attack(){
    if((target->getPosition()-position).GetLength() <= range){
		setAttackSprite();
        target->receiveDamage(getDamage(target), this);
		s3eDebugOutputString("attack!");
    }
}

int Wrecker::getDamage(Unit* unit){
    unit_type type = unit->getType();
    return statAttacks[type];
}

