#include "aabb.h"

AABB::AABB(float x1, float y1, float x2, float y2)
	:b_left(x1, y1), t_right(x2, y2)
{
}

AABB::AABB(const CIwFVec2& bottom_left, const CIwFVec2& top_right)
	:b_left(bottom_left), t_right(top_right)
{
}

bool AABB::Intersect(float x, float y)
{
	return ((b_left.x < x) && (b_left.y > y)) && ((t_right.x > x) && (t_right.y < y));
}

bool AABB::Intersect(const CIwFVec2& point)
{
	return ((b_left.x < point.x) && (b_left.y > point.y)) && ((t_right.x > point.x) && (t_right.y < point.y));
}
