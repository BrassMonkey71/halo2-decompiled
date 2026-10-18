// @flags /O2 /GL-
// Havok (third-party physics library): a box's half extents, and its corner
// furthest along a direction (w tags which corner).
#include <xmmintrin.h>

static __declspec(align(16)) const unsigned long g_4124a0[4] = {0x80000000, 0x80000000, 0x80000000, 0x80000000};

class class_2fe410
{
public:
	long field_0;
	long field_4;
	long field_8;
	long field_c;
	__m128 half_extents;

	void get_half_extents(__m128 *out) const;
	void get_support(const __m128 *direction, __m128 *out) const;
};

// @retail 0x2fe410
void class_2fe410::get_half_extents(__m128 *out) const
{
	*out = half_extents;
}

// @retail 0x2fe450
void class_2fe410::get_support(const __m128 *direction, __m128 *out) const
{
	__m128 corner = half_extents;
	*out = corner;
	corner = _mm_xor_ps(corner, _mm_and_ps(*direction, *(const __m128 *)g_4124a0));
	*out = corner;
	((unsigned long *)out)[3] = (_mm_movemask_ps(corner) & 7) | 0x3f000000;
}
