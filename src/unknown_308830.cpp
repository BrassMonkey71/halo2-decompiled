// @flags /O2 /GL-
// Havok (third-party physics library): the point of a segment closest to a
// given point, with which part of the segment it is.
#include <xmmintrin.h>

// three-term dot product of two vectors
inline void dot3_308830(float *result, __m128 const &a, __m128 const &b)
{
	__m128 const product = _mm_mul_ps(a, b);
	_mm_store_ss(result, _mm_add_ss(_mm_shuffle_ps(product, product, 0xaa), _mm_add_ss(_mm_shuffle_ps(product, product, 0x55), product)));
}

// out: start (returns 8) when the point projects before it, end (returns 4)
// when it projects past it, else the projection itself (returns 0)
// @retail 0x308830
long __cdecl function_308830(__m128 const &point, __m128 const &start, __m128 const &end, __m128 &out)
{
	__m128 const b = start;
	__m128 const direction = _mm_sub_ps(end, b);
	float along;
	dot3_308830(&along, direction, _mm_sub_ps(b, point));
	float length_squared;
	dot3_308830(&length_squared, direction, direction);
	if ((along = -along) <= 0.0f)
	{
		out = b;
		return 8;
	}
	if (along >= length_squared)
	{
		out = _mm_add_ps(b, direction);
		return 4;
	}
	__m128 const single = _mm_set_ss(along / length_squared);
	out = _mm_add_ps(b, _mm_mul_ps(_mm_shuffle_ps(single, single, 0), direction));
	return 0;
}
