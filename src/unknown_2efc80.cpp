// @flags /O2 /GL-
// Havok (third-party physics library): two spheres reported as a pair when
// their centres are closer than the sum of their radii, as a method and as a
// free function, each bracketed by two marks in the timing stream.
#include "timer_mark_2ebc80.h"
#include <xmmintrin.h>

struct sphere_2efc80
{
	char unknown0[0xc];
	float radius;
};

struct motion_2efc80
{
	char unknown0[0x50];
	__m128 position;
};

struct body_2efc80
{
	sphere_2efc80 const *shape;
	long key;
	motion_2efc80 const *motion;
};

class collector_2efc80
{
public:
	virtual void slot_0() {}
	virtual void add_pair(body_2efc80 const *a, body_2efc80 const *b) {}
};

class sphere_pair_2efc80
{
public:
	void function_2efc80(body_2efc80 const *a, body_2efc80 const *b, void const *input, collector_2efc80 *collector);
};

// whether two spheres overlap: the squared distance of their centres against
// the squared sum of their radii
__forceinline bool overlap_2efc80(body_2efc80 const *a, body_2efc80 const *b)
{
	__m128 const offset = _mm_sub_ps(b->motion->position, a->motion->position);
	__m128 const squares = _mm_mul_ps(offset, offset);
	float distance_squared;
	_mm_store_ss(&distance_squared, _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares)));
	float const radius = a->shape->radius + b->shape->radius;
	return distance_squared < radius * radius;
}

// @retail 0x2efc80
void sphere_pair_2efc80::function_2efc80(body_2efc80 const *a, body_2efc80 const *b, void const *input, collector_2efc80 *collector)
{
	timer_add_2ebc80("TtSphereSphere");
	if (overlap_2efc80(a, b))
	{
		collector->add_pair(a, b);
	}
	timer_add_2ebc80("Et");
}

// @retail 0x2efd50
void __cdecl function_2efd50(body_2efc80 const *a, body_2efc80 const *b, void const *input, collector_2efc80 *collector)
{
	timer_add_2ebc80("TtSphereSphere");
	if (overlap_2efc80(a, b))
	{
		collector->add_pair(a, b);
	}
	timer_add_2ebc80("Et");
}
