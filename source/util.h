#ifndef _UTIL_H_
#define _UTIL_H_

#define TO_RADIANS(X) X * (180.0f / PI) 

#include "IwGx.h"
#include "IwGeom.h"

CIwFMat2D& worldToScreenMatrix(float r, float theta, int screen_width, int screen_height);

void renderImageWorldSpace(CIwFVec2 position, float angle, float scaleFactor, int textureSize, int frameNumber = 0, int numFrames = 1);

#endif