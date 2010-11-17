#include "aabb.h"

AABB::AABB(float x1, float y1, float x2, float y2)
	:b_left(x1, y1), t_right(x2, y2)
{

}
