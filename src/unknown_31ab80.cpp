// @flags /O2 /GL-
// Havok (third-party physics library): an object's rotated diagonal matrix,
// R * D * R^T, and the same with the diagonal's reciprocals.
#include <xmmintrin.h>

static inline __m128 splat_31ab80(float value)
{
	__m128 v = _mm_set_ss(value);
	return _mm_shuffle_ps(v, v, 0);
}

// the declarations the called rotation functions use (src/unknown_2da930.cpp)
struct hkVector4
{
	__m128 value;
};

struct hkRotation
{
	hkVector4 m_col0;
	hkVector4 m_col1;
	hkVector4 m_col2;
};

struct s_2da8c0
{
	hkRotation field_0;

	void function_2da930(hkRotation const *arg_0, hkRotation const *arg_1);
	void function_2da9a0(hkRotation const *arg_0);
};

inline void set_diagonal_31ab80(hkRotation *rows, float x, float y, float z)
{
	rows->m_col0.value = _mm_setzero_ps();
	rows->m_col1.value = _mm_setzero_ps();
	rows->m_col2.value = _mm_setzero_ps();
	rows->m_col0.value.m128_f32[0] = x;
	rows->m_col1.value.m128_f32[1] = y;
	rows->m_col2.value.m128_f32[2] = z;
}

class class_31ab80
{
public:
	char unknown0[0x80];
	hkRotation rotation;
	char unknownb0[0x30];
	float diagonal[3];

	void function_31ab80(s_2da8c0 *out) const;
	void function_31ac20(s_2da8c0 *out) const;
};

// @retail 0x31ab80
void class_31ab80::function_31ab80(s_2da8c0 *out) const
{
	hkRotation scaled;
	scaled.m_col0.value = _mm_mul_ps(splat_31ab80(diagonal[0]), rotation.m_col0.value);
	scaled.m_col1.value = _mm_mul_ps(splat_31ab80(diagonal[1]), rotation.m_col1.value);
	scaled.m_col2.value = _mm_mul_ps(splat_31ab80(diagonal[2]), rotation.m_col2.value);
	out->function_2da930(&scaled, &rotation);
}

// @retail 0x31ac20
// not matched yet: retail stores the second reciprocal before the copy of
// the third
void class_31ab80::function_31ac20(s_2da8c0 *out) const
{
	float x = 1.0f / diagonal[0];
	float y = 1.0f / diagonal[1];
	float z = 1.0f / diagonal[2];
	set_diagonal_31ab80(&out->field_0, x, y, z);
	out->function_2da9a0(&rotation);
}
