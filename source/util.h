#ifndef _UTIL_H_
#define _UTIL_H_

#define TO_RADIANS(X) X * (180.0f / PI) 

#include "IwGx.h"
#include "IwGeom.h"

void renderImageWorldSpace(CIwSVec2 position, float angle, float scaleFactor, int textureSize, float worldRot = 0.0, int frameNumber = 0, int numFrames = 1);

#endif