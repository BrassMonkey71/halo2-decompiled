// @flags /O2 /GL-
// Havok (third-party physics library): a sphere and a capsule reported as a
// pair when the sphere's centre is closer to the capsule's segment than the
// sum of their radii, bracketed by two marks in the timing stream.
#include "pair_collector_2f09b0.h"
#include "timer_mark_2ebc80.h"
#include <xmmintrin.h>

// the point of a segment nearest a point (0x308830)
long __cdecl function_308830(__m128 const &point, __m128 const &start, __m128 const &end, __m128 &out);

struct sphere_2f09b0
{
	char unknown0[0xc];
	float radius;
};

// a capsule: its radius and the two ends of its segment
struct capsule_2f09b0
{
	char unknown0[0xc];
	float radius;
	__m128 ends[2];
};

// three axes and a position
struct transform_2f09b0
{
	__m128 axes[3];
	__m128 position;
};

struct motion_2f09b0
{
	char unknown0[0x20];
	transform_2f09b0 transform;
};

struct body_2f09b0
{
	void const *shape;
	long key;
	motion_2f09b0 const *motion;
};

// a point placed by a transform
struct point_2f09b0
{
	__m128 value;

	void set_transformed(transform_2f09b0 const *transform, __m128 const *point)
	{
		__m128 p = *point;
		__m128 z = _mm_add_ps(_mm_mul_ps(transform->axes[2], _mm_shuffle_ps(p, p, 0xaa)), transform->position);
		__m128 y = _mm_mul_ps(transform->axes[1], _mm_shuffle_ps(p, p, 0x55));
		__m128 x = _mm_mul_ps(transform->axes[0], _mm_shuffle_ps(p, p, 0x00));
		value = _mm_add_ps(_mm_add_ps(x, y), z);
	}
};

// @retail 0x2f09b0
void __cdecl function_2f09b0(body_2f09b0 const *a, body_2f09b0 const *b, void const *input, collector_2f09b0 *collector)
{
	timer_add_2ebc80("TtSphereCapsule");
	sphere_2f09b0 const *sphere = (sphere_2f09b0 const *)a->shape;
	capsule_2f09b0 const *capsule = (capsule_2f09b0 const *)b->shape;
	__m128 const *centre = &a->motion->transform.position;
	point_2f09b0 ends[2];
	__m128 const *vertex = capsule->ends;
	transform_2f09b0 const *transform = &b->motion->transform;
	point_2f09b0 *end = ends;
	for (int count = 2; count != 0; count--)
	{
		end->set_transformed(transform, vertex);
		end++;
		vertex++;
	}
	__m128 nearest;
	function_308830(*centre, ends[0].value, ends[1].value, nearest);
	float const radius = capsule->radius + sphere->radius;
	__m128 const offset = _mm_sub_ps(nearest, *centre);
	__m128 const squares = _mm_mul_ps(offset, offset);
	float distance_squared;
	_mm_store_ss(&distance_squared, _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares)));
	if (distance_squared < radius * radius)
	{
		collector->add_pair(a, b);
	}
	timer_add_2ebc80("Et");
}
