#ifndef _WORLD_OBJECT_H_
#define _WORLD_OBJECT_H_

#include "IwGx.h"
#include "IwGeom.h"
#include "IwGeomCore.h"
#include <string>
#include <vector>

class Game;

#include "util.h"

/**
A WorldObject represents some object (right now, either icing or a unit) that lives in
the game world. A WorldObject knows a minimum of three things - its coordinates ((x,y) 
and (r, theta)), the name of its texture, and how to render itself in world space.
*/
class WorldObject {
	
	public:
        WorldObject(Game *game);
		WorldObject(CIwFVec2 position, Game* game);
		
		WorldObject(const WorldObject& newObj);
	
		virtual ~WorldObject() { };
	
		void setPosition(float x, float y);
	
		void setPosition(const CIwFVec2& position);
	
		CIwFVec2 getPosition();	
	
		float getX();
	
		float getY();
	
		void setPolarPosition(float _r, float _theta);

		float getR();
	
		float getTheta();
		
		Game* getGame();
	
		virtual void display() = 0;

		virtual unsigned int getTextureName();


	protected:
		
		Game* game;
	
		CIwFVec2 position;
		
		float r, theta;

		// A vector of hashes of texture names for this unit
		std::vector<unsigned int> texture_names;

		// Index into the texture container representing the current active texture
		// 0 is the default
		int current_texture_index;
	
};

#endif
