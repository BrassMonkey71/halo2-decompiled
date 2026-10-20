// @flags /O2 /GL-
// Havok (third-party physics library): whether two capsules overlap: the
// closest points of their segments, in the world, against the sum of their
// radii; a pair that overlaps is passed to the collector. The query is marked
// in the timing stream.
#include "timer_mark_2ebc80.h"
#include <xmmintrin.h>

// three axes and a position (0x2da4d0)
struct c_query_transform
{
	__m128 axes[3];
	__m128 position;
};

// a point taken out of a transform's frame (0x2da610, inlined here)
inline __m128 transform_point_2f40e0(c_query_transform const *m, __m128 const *point)
{
	__m128 p = *point;
	__m128 z = _mm_add_ps(_mm_mul_ps(m->axes[2], _mm_shuffle_ps(p, p, 0xaa)), m->position);
	__m128 y = _mm_mul_ps(m->axes[1], _mm_shuffle_ps(p, p, 0x55));
	__m128 x = _mm_mul_ps(m->axes[0], _mm_shuffle_ps(p, p, 0x00));
	return _mm_add_ps(_mm_add_ps(x, y), z);
}

// where a body sits: two vectors, then its transform
struct placement_2f40e0
{
	__m128 field_0;
	__m128 field_10;
	c_query_transform transform;
};

// a capsule: its radius and the two ends of its segment
struct capsule_2f40e0
{
	void const *table;
	long field_4;
	long field_8;
	float radius;
	__m128 ends[2];
};

// one side of a query: a shape, the key of the part concerned, where it sits,
// and the side it is a part of
struct body_2f40e0
{
	capsule_2f40e0 const *shape;
	long key;
	placement_2f40e0 const *placement;
	body_2f40e0 const *parent;
};

// takes the pairs a query finds
class collector_2f40e0
{
public:
	virtual void slot_0() {}
	virtual void add_pair(void const *a, void const *b) {}
};

// the closest point on the first segment, the offset from the closest point
// on the second, and the square of that offset's length (0x308590)
struct closest_points_308590
{
	__m128 first_point;
	__m128 offset;
	float distance_squared;
};

int __cdecl function_308590(__m128 const *first_start, __m128 const *first_direction, __m128 const *second_start, __m128 const *second_direction, closest_points_308590 *result);

// @retail 0x2f40e0
void __cdecl function_2f40e0(void const *a, void const *b, void const *input, void *collector)
{
	timer_add_2ebc80("TtCapsCaps");
	body_2f40e0 const *side_a = (body_2f40e0 const *)a;
	body_2f40e0 const *side_b = (body_2f40e0 const *)b;
	capsule_2f40e0 const *capsule_a = side_a->shape;
	capsule_2f40e0 const *capsule_b = side_b->shape;
	__m128 ends_a[2];
	{
		c_query_transform const *frame = &side_a->placement->transform;
		__m128 const *end = capsule_a->ends;
		__m128 *placed = ends_a;
		for (int count = 2; count != 0; count--)
		{
			*placed = transform_point_2f40e0(frame, end);
			placed++;
			end++;
		}
	}
	__m128 ends_b[2];
	{
		c_query_transform const *frame = &side_b->placement->transform;
		__m128 const *end = capsule_b->ends;
		__m128 *placed = ends_b;
		for (int count = 2; count != 0; count--)
		{
			*placed = transform_point_2f40e0(frame, end);
			placed++;
			end++;
		}
	}
	__m128 direction_a = _mm_sub_ps(ends_a[1], ends_a[0]);
	__m128 direction_b = _mm_sub_ps(ends_b[1], ends_b[0]);
	closest_points_308590 closest;
	function_308590(&ends_a[0], &direction_a, &ends_b[0], &direction_b, &closest);
	float radius = capsule_b->radius + capsule_a->radius;
	if (closest.distance_squared < radius * radius)
	{
		((collector_2f40e0 *)collector)->add_pair(a, b);
	}
	timer_add_2ebc80("Et");
}
