#ifndef _SPREADER_H
#define _SPREADER_H

#include "unit.h"

class Spreader : public Unit {
    private:
	
        int amountSpread;
		int spreadDelay;
		CIwFVec2 worldRad;
    
	public:
		Spreader(Player* owner, Game* game, float x, float y);
		Spreader(const Spreader& newSpreader);
		~Spreader(){};

		virtual bool update();
        virtual const char* getTextureName();
		virtual unit_type getType();
	
		virtual Unit* spawnCopy();
    
};

#endif
