#ifndef _UTIL_H_
#define _UTIL_H_

#define TO_RADIANS(X) X * (PI / 180.0f) 

#include "IwGx.h"
#include "IwGeom.h"

void renderImageWorldSpace(CIwFVec2 position, float angle, float scaleFactor, int textureSize, float worldRot = 0.0, int frameNumber = 0, int numFrames = 1);

CIwFMat2D& worldToScreenMatrix(float r, float theta, int screen_width, int screen_height);

#endif