// @flags /O2 /GL-
// Havok (third-party physics library): a triangle's edge and area measures:
// the inverse length of each edge, and twice its area with its inverse.
#include <xmmintrin.h>

struct triangle_measures_308a50
{
	float inverse_edge_lengths[3];
	float inverse_double_area;
	float double_area;
};

// each inverse length is the estimate refined by one Newton step
// @retail 0x308a50
void __cdecl function_308a50(__m128 const *vertices, triangle_measures_308a50 *measures)
{
	__m128 const edge_0 = _mm_sub_ps(vertices[2], vertices[1]);
	__m128 const edge_2 = _mm_sub_ps(vertices[0], vertices[2]);
	__m128 const edge_1 = _mm_sub_ps(vertices[1], vertices[0]);

	__m128 squares = _mm_mul_ps(edge_0, edge_0);
	__m128 sum = _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares));
	__m128 estimate = _mm_rsqrt_ss(sum);
	__m128 correction = _mm_sub_ss(_mm_set_ss(3.0f), _mm_mul_ss(_mm_mul_ss(sum, estimate), estimate));
	float first_inverse_length;
	_mm_store_ss(&first_inverse_length, _mm_mul_ss(_mm_mul_ss(_mm_set_ss(0.5f), estimate), correction));
	measures->inverse_edge_lengths[0] = first_inverse_length;

	squares = _mm_mul_ps(edge_2, edge_2);
	sum = _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares));
	estimate = _mm_rsqrt_ss(sum);
	correction = _mm_sub_ss(_mm_set_ss(3.0f), _mm_mul_ss(_mm_mul_ss(sum, estimate), estimate));
	float second_inverse_length;
	_mm_store_ss(&second_inverse_length, _mm_mul_ss(_mm_mul_ss(_mm_set_ss(0.5f), estimate), correction));
	measures->inverse_edge_lengths[1] = second_inverse_length;

	squares = _mm_mul_ps(edge_1, edge_1);
	sum = _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares));
	estimate = _mm_rsqrt_ss(sum);
	correction = _mm_sub_ss(_mm_set_ss(3.0f), _mm_mul_ss(_mm_mul_ss(sum, estimate), estimate));
	float third_inverse_length;
	_mm_store_ss(&third_inverse_length, _mm_mul_ss(_mm_mul_ss(_mm_set_ss(0.5f), estimate), correction));
	measures->inverse_edge_lengths[2] = third_inverse_length;

	__m128 const normal = _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(edge_0, edge_0, 0xc9), _mm_shuffle_ps(edge_2, edge_2, 0xd2)),
		_mm_mul_ps(_mm_shuffle_ps(edge_0, edge_0, 0xd2), _mm_shuffle_ps(edge_2, edge_2, 0xc9)));
	squares = _mm_mul_ps(normal, normal);
	__m128 const area_squared = _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares));
	float double_area;
	_mm_store_ss(&double_area, _mm_sqrt_ss(area_squared));
	measures->inverse_double_area = 1.0f / double_area;
	measures->double_area = double_area;
}
