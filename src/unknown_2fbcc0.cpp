// @flags /O2 /GL-
// Havok (third-party physics library): a container of parts: its bounding
// box and its furthest reach along a direction, gathered over its parts,
// each bracketed by two marks in the timing stream.
#include "timer_mark_2ebc80.h"
#include <xmmintrin.h>

struct bounds_2fbcc0
{
	__m128 lower;
	__m128 upper;
};

class part_2fbcc0
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual void slot_5() {}
	// the bounding box under a transform, grown by a tolerance
	virtual void bounds(void const *transform, float tolerance, bounds_2fbcc0 *out) const {}
	// the furthest reach along a direction
	virtual float reach(__m128 const *direction) const { return 0.0f; }
};

class container_2fbcc0
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual void slot_5() {}
	virtual void slot_6() {}
	virtual void slot_7() {}
	virtual void slot_8() {}
	virtual void slot_9() {}
	virtual void slot_10() {}
	// the part keys, ending with -1
	virtual long first_key() const { return -1; }
	virtual long next_key(long key) const { return -1; }
	// a part, built in the buffer given when it must be
	virtual part_2fbcc0 const *part(long key, char *buffer) const { return 0; }

	void function_2fbcc0(void const *transform, float tolerance, bounds_2fbcc0 *out) const;
	float function_2fbdc0(__m128 const *direction) const;
};

// the box around every part's box: the first part's box, then every part's
// box merged in (zero when there are no parts)
// @retail 0x2fbcc0
void container_2fbcc0::function_2fbcc0(void const *transform, float tolerance, bounds_2fbcc0 *out) const
{
	timer_add_2ebc80("TthkShapeCollection::getAabb");
	__declspec(align(16)) char buffer[0x100];
	bounds_2fbcc0 bounds;
	out->lower = _mm_setzero_ps();
	out->upper = _mm_setzero_ps();
	long key = first_key();
	if (key != -1)
	{
		part(key, buffer)->bounds(transform, tolerance, out);
		do
		{
			part(key, buffer)->bounds(transform, tolerance, &bounds);
			out->lower = _mm_min_ps(_mm_load_ps((float const *)&out->lower), bounds.lower);
			out->upper = _mm_max_ps(out->upper, bounds.upper);
			key = next_key(key);
		}
		while (key != -1);
	}
	timer_add_2ebc80("Et");
}

// the largest reach of any part
// @retail 0x2fbdc0
float container_2fbcc0::function_2fbdc0(__m128 const *direction) const
{
	timer_add_2ebc80("TthkShapeCollection::getMaximumProjection");
	__declspec(align(16)) char buffer[0x100];
	float best = -3.40282347e+38f;
	for (long key = first_key(); key != -1; key = next_key(key))
	{
		float const reach = part(key, buffer)->reach(direction);
		best = best > reach ? best : reach;
	}
	timer_add_2ebc80("Et");
	return best;
}
