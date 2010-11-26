#include "worldobject.h"
#include "game.h"
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