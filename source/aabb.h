#ifndef _AABB_H
#define _AABB_H

#include "IwGeom.h"

class AABB {
public:
	AABB(float x1, float y1, float x2, float y2);
	AABB(const cIwSVec2& bottom_left, const cIwSVec2& top_right);

	~AABB();

	bool Intersect(float x, float y);
	bool Intersect(const cIwSVec2& point);
private:
	cIwSVec2 b_left;
	cIwSVec2 t_right;
};

#endif