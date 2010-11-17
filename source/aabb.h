#ifndef _AABB_H
#define _AABB_H

#include "IwGeom.h"

class AABB {
public:
	AABB(float x1, float y1, float x2, float y2);
	AABB(const CIwFVec2& bottom_left, const CIwFVec2& top_right);

	~AABB();

	/**
	 * Intersect this bounding volume with a point (x,y)
	 */
	bool Intersect(float x, float y);

	/**
	 * Intersect this bounding volume with a point.
	 */
	bool Intersect(const CIwFVec2& point);
private:
	CIwFVec2 b_left;
	CIwFVec2 t_right;
};

#endif