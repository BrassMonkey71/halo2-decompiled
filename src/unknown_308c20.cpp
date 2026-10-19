// @flags /O2 /GL-
// Havok (third-party physics library): a triangle's weighted edge planes as
// a 4x4 matrix: each weighted edge crossed with the weighted normal gives a
// column, the normal is the fourth column, and the last row holds minus the
// product of two of the weights.
#include <xmmintrin.h>

// the cross product of two vectors' first three terms
inline __m128 cross_308c20(__m128 const &a, __m128 const &b)
{
	return _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(a, a, 0xc9), _mm_shuffle_ps(b, b, 0xd2)),
		_mm_mul_ps(_mm_shuffle_ps(a, a, 0xd2), _mm_shuffle_ps(b, b, 0xc9)));
}

// a vector of four copies of a float
inline __m128 splat_308c20(float value)
{
	__m128 const single = _mm_set_ss(value);
	return _mm_shuffle_ps(single, single, 0);
}

// two floats exchanged
inline void swap_308c20(float &a, float &b)
{
	float const old_a = a;
	float const old_b = b;
	a = old_b;
	b = old_a;
}

// the weight of each edge, of the normal, and of the last row
struct weights_308c20
{
	float edges[3];
	float normal;
	float last;
};

// a vector set in place
struct vector_308c20
{
	__m128 value;

	void set_cross(__m128 const &a, __m128 const &b) { value = cross_308c20(a, b); }
};

struct matrix_308c20
{
	vector_308c20 rows[4];
};

// @retail 0x308c20
void __cdecl function_308c20(__m128 const *corners, weights_308c20 const *weights, matrix_308c20 *out, __m128 *normal)
{
	__m128 const edge_0 = _mm_sub_ps(corners[2], corners[1]);
	__m128 const edge_1 = _mm_sub_ps(corners[0], corners[2]);
	__m128 const edge_2 = _mm_sub_ps(corners[1], corners[0]);
	__m128 const scaled_normal = _mm_mul_ps(splat_308c20(weights->normal), cross_308c20(edge_0, edge_1));
	*normal = scaled_normal;
	__m128 const weighted_0 = _mm_mul_ps(splat_308c20(weights->edges[0]), edge_0);
	__m128 const weighted_1 = _mm_mul_ps(splat_308c20(weights->edges[1]), edge_1);
	__m128 const weighted_2 = _mm_mul_ps(splat_308c20(weights->edges[2]), edge_2);
	out->rows[0].set_cross(weighted_0, scaled_normal);
	out->rows[1].set_cross(weighted_1, scaled_normal);
	out->rows[2].set_cross(weighted_2, scaled_normal);
	float *terms = (float *)out->rows;
	swap_308c20(terms[4], terms[1]);
	swap_308c20(terms[8], terms[2]);
	swap_308c20(terms[9], terms[6]);
	float const *normal_terms = (float const *)normal;
	terms[3] = normal_terms[0];
	terms[7] = normal_terms[1];
	terms[11] = normal_terms[2];
	out->rows[3].value = _mm_setzero_ps();
	terms[12] = -(weights->last * weights->edges[0]);
}
