#ifndef _SPREADER_H
#define _SPREADER_H

#include <stdlib.h>
#include <hash_map>
#include <utility>

#include "unit.h"
#include "icing.h"
#include <cmath>

typedef std::map<std::pair<int, float>, bool> IceMap;

class Spreader : public Unit {
    private:
        // The maximum radii at which to drop icing.
	    int maxSpread;

        // The number of ticks since the last icing drop.
        int sinceLastSpread;

        // The delay between dropping an icing.
		int spreadDelay;
        
        // The maximum number of individual icing to drop. Precomputed at construction.
        int maxIcingCount;

        // The current iteration step being used to wind around the spreader's icing radius
        float currentJump;

        // The current radius where icing is being generated around the spreader.
        int currentRadius;

        // The maximum amount of icing that can fit on the current radius.
        int radiusMaxIcing;

        // The total icing spawned on the current radius.
        int icingThisRadius;

		CIwFVec2 worldRad;

        // Map from (r, theta) centered at the spreader's center to icing pointers.
        IceMap icingMap;
    
	public:
		Spreader(Player* owner, Game* game, float x, float y);
		Spreader(const Spreader& newSpreader);
		~Spreader();

		virtual bool update(std::list<Unit*>::iterator itr);

		virtual unit_type getType();
		virtual Unit* spawnCopy();
        virtual bool shouldAIUpdate();
        IceMap* getIcing();
};

#endif
