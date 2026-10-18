// @flags /O2 /GL-
// Havok (third-party physics library): a diagonal 3x3 matrix from three
// values.
#include <xmmintrin.h>

inline void set_diagonal_31ab30(__m128 *rows, float x, float y, float z)
{
	rows[0] = _mm_setzero_ps();
	rows[1] = _mm_setzero_ps();
	rows[2] = _mm_setzero_ps();
	rows[0].m128_f32[0] = x;
	rows[1].m128_f32[1] = y;
	rows[2].m128_f32[2] = z;
}

class class_31ab30
{
public:
	char unknown0[0xe0];
	float diagonal[3];

	void get_matrix(__m128 *rows) const;
};

// @retail 0x31ab30
void class_31ab30::get_matrix(__m128 *rows) const
{
	set_diagonal_31ab30(rows, diagonal[0], diagonal[1], diagonal[2]);
}
