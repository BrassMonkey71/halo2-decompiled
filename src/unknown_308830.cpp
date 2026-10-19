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

// the cross product of two vectors' first three terms
inline __m128 cross_308910(__m128 const &a, __m128 const &b)
{
	return _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(a, a, 0xc9), _mm_shuffle_ps(b, b, 0xd2)),
		_mm_mul_ps(_mm_shuffle_ps(a, a, 0xd2), _mm_shuffle_ps(b, b, 0xc9)));
}

// a vector's first term
inline float first_term_308910(__m128 const &v)
{
	float result;
	_mm_store_ss(&result, v);
	return result;
}

// a triangle's two edges from its second corner, as the terms that solve for
// a point's weights in its plane: the edges' squared lengths and their dot
// product over the determinant, then one over the length of their cross
// product
// @retail 0x308910
void __cdecl function_308910(__m128 const *corners, float *out)
{
	__m128 const edge_a = _mm_sub_ps(corners[0], corners[1]);
	__m128 const edge_b = _mm_sub_ps(corners[2], corners[1]);
	float length_a_squared;
	dot3_308830(&length_a_squared, edge_a, edge_a);
	float length_b_squared;
	dot3_308830(&length_b_squared, edge_b, edge_b);
	float edges_dot;
	dot3_308830(&edges_dot, edge_b, edge_a);
	float const inverse = 1.0f / (length_b_squared * length_a_squared - edges_dot * edges_dot);
	__m128 const normal = cross_308910(edge_a, edge_b);
	__m128 const squares = _mm_mul_ps(normal, normal);
	__m128 const length = _mm_sqrt_ss(_mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares)));
	out[0] = length_a_squared * inverse;
	out[1] = length_b_squared * inverse;
	out[2] = edges_dot * inverse;
	out[3] = 1.0f / first_term_308910(length);
}
