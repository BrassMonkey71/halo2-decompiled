// @flags /O2 /GL-
// Havok (third-party physics library): the weights of a point against the
// three corners of a triangle; for a triangle with no area, the weights
// against the ends of its longest edge.
#include <xmmintrin.h>

// the dot product of two vectors' first three terms
__forceinline void dot3_308260(float *result, __m128 const &a, __m128 const &b)
{
	__m128 const product = _mm_mul_ps(a, b);
	_mm_store_ss(result, _mm_add_ss(_mm_shuffle_ps(product, product, 0xaa), _mm_add_ss(_mm_shuffle_ps(product, product, 0x55), product)));
}

// @retail 0x308260
void __cdecl function_308260(__m128 const *point, __m128 const *a, __m128 const *b, __m128 const *c, float *weights)
{
	__m128 const ab = _mm_sub_ps(*a, *b);
	__m128 const cb = _mm_sub_ps(*c, *b);
	float ab_squared;
	dot3_308260(&ab_squared, ab, ab);
	float cb_squared;
	dot3_308260(&cb_squared, cb, cb);
	float cross;
	dot3_308260(&cross, cb, ab);
	float const determinant = cb_squared * ab_squared - cross * cross;
	if (determinant > 0.0f)
	{
		float const inverse = 1.0f / determinant;
		__m128 const to_b = _mm_sub_ps(*b, *point);
		float along_ab;
		dot3_308260(&along_ab, to_b, ab);
		float along_cb;
		dot3_308260(&along_cb, to_b, cb);
		float const s = along_cb * cross - along_ab * cb_squared;
		float const t = cross * along_ab - along_cb * ab_squared;
		weights[0] = s * inverse;
		weights[1] = (determinant - s - t) * inverse;
		weights[2] = t * inverse;
	}
	else
	{
		__m128 const ac = _mm_sub_ps(*a, *c);
		float ac_squared;
	dot3_308260(&ac_squared, ac, ac);
		if (ab_squared >= cb_squared)
		{
			if (ac_squared >= ab_squared)
			{
				weights[1] = 0.0f;
				if (ac_squared > 0.0f)
				{
					float along;
					dot3_308260(&along, _mm_sub_ps(*point, *c), ac);
					float const t = along / ac_squared;
					weights[0] = t;
					weights[2] = 1.0f - t;
				}
				else
				{
					weights[0] = 0.0f;
					weights[2] = 0.0f;
				}
			}
			else
			{
				float along;
				dot3_308260(&along, _mm_sub_ps(*point, *b), ab);
				float const t = along / ab_squared;
				weights[0] = t;
				weights[1] = 1.0f - t;
				weights[2] = 0.0f;
			}
		}
		else if (ac_squared >= cb_squared)
		{
			float along;
			dot3_308260(&along, _mm_sub_ps(*point, *c), ac);
			float const t = along / ac_squared;
			weights[0] = t;
			weights[1] = 0.0f;
			weights[2] = 1.0f - t;
		}
		else
		{
			float along;
			dot3_308260(&along, _mm_sub_ps(*point, *b), cb);
			float const t = along / cb_squared;
			weights[0] = 0.0f;
			weights[2] = t;
			weights[1] = 1.0f - t;
		}
	}
}
