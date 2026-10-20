// @flags /O2 /GL-
// Havok (third-party physics library): builds a capsule between two points
// with a radius, the radius also in each point's fourth lane. It is the
// object 0x2de750 builds from a description (vtable 0x455458), here under the
// name the game's code constructs it by (include/unknown_0a9f20.h).
#include "shape_2de750.h"

// a point whose lanes can be reached one at a time
struct point_2de0a0
{
	__m128 value;

	float &operator()(int i) { return ((float *)&value)[i]; }
};

class c_z_capsule_temp : public radius_shape_2de750
{
public:
	point_2de0a0 first;
	point_2de0a0 second;

	c_z_capsule_temp(void const *first, void const *second, float radius);
};

// @retail 0x2de0a0
c_z_capsule_temp::c_z_capsule_temp(void const *first_, void const *second_, float radius_)
	: radius_shape_2de750(radius_)
{
	first.value = *(__m128 const *)first_;
	second.value = *(__m128 const *)second_;
	first(3) = radius_;
	second(3) = radius_;
}
