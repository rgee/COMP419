#ifndef _ICING_H_
#define _ICING_H_

#include "IwRandom.h"
#include "worldobject.h"
#include "player.h"

class Icing : public WorldObject {
	
	private:
	
		Player* owner;
	
		float angle;
	
		float scale;
	
		float finalScale;
	
	public:
	
		Icing(const CIwFVec2 position, Game* game, Player* owner);
	
		Icing(const Icing& newIcing);
	
		Player* getOwner();
	
		virtual void display();
	
		virtual const char* getTextureName();

	
};

#endif
