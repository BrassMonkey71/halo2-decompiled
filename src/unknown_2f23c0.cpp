// @flags /O2 /GL-
// Havok (third-party physics library): a sphere and a box reported as a pair
// when the sphere's centre is closer to the box than the sum of their radii,
// bracketed by two marks in the timing stream.
#include "timer_mark_2ebc80.h"
#include <xmmintrin.h>

static __declspec(align(16)) const unsigned long g_sign_mask_4124a0[4] = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
static __declspec(align(16)) const unsigned long g_magnitude_mask_455940[4] = {0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff};

// three axes and a position
struct c_query_transform
{
	__m128 axes[3];
	__m128 position;
};

// a point taken into a transform's frame (0x2da660)
struct c_query_point
{
	__m128 value;
	void inverse_transform(const c_query_transform *matrix, const __m128 *point);
};

// a point placed by a transform
struct placed_point_2f23c0
{
	__m128 value;

	void set_transformed(c_query_transform const *transform, __m128 const *point)
	{
		__m128 p = *point;
		__m128 z = _mm_add_ps(_mm_mul_ps(transform->axes[2], _mm_shuffle_ps(p, p, 0xaa)), transform->position);
		__m128 y = _mm_mul_ps(transform->axes[1], _mm_shuffle_ps(p, p, 0x55));
		__m128 x = _mm_mul_ps(transform->axes[0], _mm_shuffle_ps(p, p, 0x00));
		value = _mm_add_ps(_mm_add_ps(x, y), z);
	}
};

struct sphere_2f23c0
{
	char unknown0[0xc];
	float radius;
};

// a box: its radius and its half extents
struct box_2f23c0
{
	char unknown0[0xc];
	float radius;
	__m128 half_extents;
};

struct motion_2f23c0
{
	char unknown0[0x20];
	c_query_transform transform;
};

struct body_2f23c0
{
	void const *shape;
	long key;
	motion_2f23c0 const *motion;
};

class collector_2f23c0
{
public:
	virtual void slot_0() {}
	virtual void add_pair(body_2f23c0 const *a, body_2f23c0 const *b) {}
};

// @retail 0x2f23c0
void __cdecl function_2f23c0(body_2f23c0 const *a, body_2f23c0 const *b, void const *input, collector_2f23c0 *collector)
{
	timer_add_2ebc80("TtSphereBox");
	sphere_2f23c0 const *sphere = (sphere_2f23c0 const *)a->shape;
	box_2f23c0 const *box = (box_2f23c0 const *)b->shape;
	__m128 const *centre = &a->motion->transform.position;
	c_query_point local;
	local.inverse_transform(&b->motion->transform, centre);
	float const radius = box->radius + sphere->radius;
	__m128 const sign = _mm_and_ps(local.value, *(__m128 const *)g_sign_mask_4124a0);
	__m128 const magnitude = _mm_and_ps(local.value, *(__m128 const *)g_magnitude_mask_455940);
	placed_point_2f23c0 nearest;
	nearest.value = _mm_xor_ps(_mm_min_ps(magnitude, box->half_extents), sign);
	placed_point_2f23c0 world;
	world.set_transformed(&b->motion->transform, &nearest.value);
	__m128 const offset = _mm_sub_ps(world.value, *centre);
	__m128 const squares = _mm_mul_ps(offset, offset);
	float distance_squared;
	_mm_store_ss(&distance_squared, _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares)));
	if (distance_squared < radius * radius)
	{
		collector->add_pair(a, b);
	}
	timer_add_2ebc80("Et");
}
