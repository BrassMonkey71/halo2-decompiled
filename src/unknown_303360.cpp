// @flags /O2 /GL-
// Havok (third-party physics library): which sides of a triangle's three
// edges a point lies inside, as three sign bits; and, when asked, the
// triangle's normal kept and the triangle turned round when the point lies
// over all three edges but the normal faces away from the search direction.
#include <xmmintrin.h>

static __declspec(align(16)) const unsigned long g_4124a0[4] = {0x80000000, 0x80000000, 0x80000000, 0x80000000};

// the cross product of two vectors' first three terms
inline __m128 cross_303360(__m128 const &a, __m128 const &b)
{
	__m128 b_yzx = _mm_shuffle_ps(b, b, 0xc9);
	__m128 b_zxy = _mm_shuffle_ps(b, b, 0xd2);
	__m128 a_zxy = _mm_shuffle_ps(a, a, 0xd2);
	__m128 a_yzx = _mm_shuffle_ps(a, a, 0xc9);
	__m128 second = _mm_mul_ps(a_zxy, b_yzx);
	return _mm_sub_ps(_mm_mul_ps(a_yzx, b_zxy), second);
}

inline void swap_vectors_303360(__m128 &x, __m128 &y)
{
	__m128 t = x;
	x = y;
	y = t;
}

inline void swap_floats_303360(float &x, float &y)
{
	float t = x;
	x = y;
	y = t;
}

struct triangle_303360
{
	__m128 vertices[3];
	__m128 field_30;
	__m128 field_40;
	__m128 field_50;
};

class class_303360
{
public:
	char unknown0[0x20];
	__m128 field_20;
	char unknown30[0xa0 - 0x30];
	__m128 field_a0;
	char unknownb0[0x120 - 0xb0];
	__m128 normal;
	char unknown130[0x160 - 0x130];
	union
	{
		__m128 edge_dots;
		float edge_dot[4];
	};

	int function_303360(__m128 const *point, triangle_303360 *triangle, int orient);
};

// @retail 0x303360
int class_303360::function_303360(__m128 const *point, triangle_303360 *triangle, int orient)
{
	__m128 a = triangle->vertices[0];
	__m128 b = triangle->vertices[1];
	__m128 c = triangle->vertices[2];
	__m128 cb = _mm_sub_ps(c, b);
	__m128 ac = _mm_sub_ps(a, c);
	__m128 ba = _mm_sub_ps(b, a);
	__m128 n = cross_303360(cb, ac);
	__m128 p = *point;
	__m128 across_cb = cross_303360(_mm_sub_ps(p, b), cb);
	__m128 across_ac = cross_303360(_mm_sub_ps(p, triangle->vertices[2]), ac);
	__m128 across_ba = cross_303360(_mm_sub_ps(p, triangle->vertices[0]), ba);

	// the three cross products' dot products with the normal
	__m128 low = _mm_shuffle_ps(across_cb, across_ac, 0x44);
	__m128 last_low = _mm_shuffle_ps(across_ba, across_ba, 0x44);
	__m128 zs = _mm_shuffle_ps(_mm_shuffle_ps(across_cb, across_ac, 0xee), _mm_shuffle_ps(across_ba, across_ba, 0xee), 0x88);
	__m128 ys = _mm_shuffle_ps(low, last_low, 0xdd);
	__m128 xs = _mm_shuffle_ps(low, last_low, 0x88);
	__m128 dots = _mm_add_ps(_mm_add_ps(
		_mm_mul_ps(xs, _mm_shuffle_ps(n, n, 0x00)),
		_mm_mul_ps(ys, _mm_shuffle_ps(n, n, 0x55))),
		_mm_mul_ps(zs, _mm_shuffle_ps(n, n, 0xaa)));

	int outside = _mm_movemask_ps(dots) & 7;
	edge_dots = dots;
	if (orient)
	{
		normal = n;
		if (outside == 7)
		{
			__m128 d = _mm_mul_ps(n, _mm_sub_ps(field_a0, field_20));
			__m128 sum = _mm_add_ss(_mm_shuffle_ps(d, d, 0xaa), _mm_add_ss(_mm_shuffle_ps(d, d, 0x55), d));
			if (_mm_movemask_ps(sum) & 1)
			{
				normal = _mm_xor_ps(n, *(__m128 const *)g_4124a0);
				swap_vectors_303360(triangle->vertices[0], triangle->vertices[1]);
				swap_vectors_303360(triangle->field_40, triangle->field_50);
				swap_floats_303360(edge_dot[0], edge_dot[1]);
			}
		}
	}
	return outside;
}
