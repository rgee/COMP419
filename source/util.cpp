#include "util.h"

void renderImageWorldSpace(CIwSVec2 position, float angle, float scaleFactor, int textureSize, float worldRot, int frameNumber, int numFrames) {
	
	int left = position.x;
	int top = position.y;
	
	static CIwSVec3 vertices[4];
	static CIwSVec2 UVs[4];
	
	//set up model space vertices
	
	int vertexDist = scaleFactor*textureSize/2;
	
	vertices[0] = CIwSVec3(-1*vertexDist, -1*vertexDist, -1);
	vertices[2] = CIwSVec3(vertexDist, -1*vertexDist, -1);
	vertices[3] = CIwSVec3(vertexDist, vertexDist, -1);
	vertices[1] = CIwSVec3(-1*vertexDist, vertexDist, -1);
	
	CIwMat modelTransform = CIwMat::g_Identity;
	modelTransform.SetRotZ(TO_RADIANS(angle));
	modelTransform.SetTrans(CIwVec3(left, -1*top, 1));
	
	CIwMat rot = CIwMat::g_Identity;
	rot.SetRotZ(TO_RADIANS(worldRot));
	modelTransform = modelTransform*rot;
	
	IwGxSetModelMatrix(&modelTransform, false);
	
	float frameRatio = (float)1/numFrames;
	
	//set up sprite UV's
	UVs[0] = CIwSVec2(0, 0);
	UVs[2] = CIwSVec2(IW_FIXED(frameRatio), 0);
	UVs[3] = CIwSVec2(IW_FIXED(frameRatio), IW_GEOM_ONE);
	UVs[1] = CIwSVec2(0, IW_GEOM_ONE);
	
	CIwSVec2 ofs = CIwSVec2(textureSize*frameNumber, 0);
	
	//render the unit in model space
	IwGxSetUVStream(UVs);
	IwGxSetUVOfs(&ofs);
	
	IwGxSetColStream(NULL);
	IwGxSetVertStreamModelSpace(vertices, 4);
	IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);
	IwGxFlush();
}