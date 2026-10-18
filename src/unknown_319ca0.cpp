// @flags /O2 /GL-
// Havok (third-party physics library): accumulating a vector and setting
// its w to one.
#include <xmmintrin.h>

class class_319ca0
{
public:
	char unknown0[0xd0];
	__m128 sum;

	void add(const __m128 &vector);
};

// @retail 0x319ca0
void class_319ca0::add(const __m128 &vector)
{
	sum = _mm_add_ps(sum, vector);
	sum.m128_f32[3] = 1.0f;
}
