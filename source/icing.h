#ifndef _ICING_H_
#define _ICING_H_

#include "worldobject.h"
#include "player.h"

class Icing : public WorldObject {
	
	private:
	
		Player* owner;
	
	public:
	
		Icing(CIwFVec2 position, Game* game);
	
		Icing(const Icing& newIcing);
	
		virtual void display();
	
		virtual const char* getTextureName();
	
};

#endif _ICING_H_