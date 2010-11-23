#include "util.h"

void renderImageWorldSpace(CIwFVec2 position, float angle, float scaleFactor, int textureSize, float worldRot, int frameNumber, int numFrames) {
	
	static CIwSVec3 vertices[4];
	static CIwSVec2 UVs[4];
	
	//set up model space vertices
	
	int vertexDist = scaleFactor*textureSize/2;
	
	vertices[0] = CIwSVec3(-1*vertexDist, -1*vertexDist, 0);
	vertices[2] = CIwSVec3(vertexDist, -1*vertexDist,    0);
	vertices[3] = CIwSVec3(vertexDist, vertexDist,       0);
	vertices[1] = CIwSVec3(-1*vertexDist, vertexDist,    0);
	
	CIwMat modelTransform = CIwMat::g_Identity;
	modelTransform.SetRotZ(IW_ANGLE_FROM_DEGREES(angle));
	modelTransform.SetTrans(CIwVec3(position.x, -position.y, 0));
	    
	CIwMat rot = CIwMat::g_Identity;
 	rot.SetRotZ(IW_ANGLE_FROM_DEGREES(worldRot));
	modelTransform = modelTransform*rot;
	
	IwGxSetModelMatrix(&modelTransform, false);
	
	float frameRatio = 1.0/numFrames;
	
	//set up sprite UV's
	UVs[0] = CIwSVec2(0, 0);
	UVs[2] = CIwSVec2(IW_FIXED(frameRatio), 0);
	UVs[3] = CIwSVec2(IW_FIXED(frameRatio), IW_GEOM_ONE);
	UVs[1] = CIwSVec2(0, IW_GEOM_ONE);
	
	CIwSVec2 ofs = CIwSVec2(textureSize*frameNumber, 0);
	
	//render the unit in model space
	IwGxSetUVStream(UVs);
	IwGxSetUVOfs(&ofs);
	
	IwGxSetVertStreamModelSpace(vertices, 4);
	IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);
	IwGxFlush();
}