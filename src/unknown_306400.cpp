// @flags /O2 /GL-
// Havok (third-party physics library): the second box's transform seen from
// the first box, and the first box's centre seen from the second.
#include <xmmintrin.h>

struct transform_306400
{
	__m128 columns[4];
};

// a direction turned by the inverse of a transform's rotation
struct vector_306400
{
	__m128 value;

	void set_inverse_rotated(transform_306400 const *transform, __m128 const *direction)
	{
		__m128 const c0 = transform->columns[0];
		__m128 const c1 = transform->columns[1];
		__m128 const c2 = transform->columns[2];
		__m128 const t0 = _mm_shuffle_ps(c0, c1, 0x44);
		__m128 const t2 = _mm_shuffle_ps(c0, c1, 0xee);
		__m128 const t1 = _mm_shuffle_ps(c2, c2, 0x44);
		__m128 const t3 = _mm_shuffle_ps(c2, c2, 0xee);
		__m128 const row_0 = _mm_shuffle_ps(t0, t1, 0x88);
		__m128 const row_1 = _mm_shuffle_ps(t0, t1, 0xdd);
		__m128 const row_2 = _mm_shuffle_ps(t2, t3, 0x88);
		__m128 const d = *direction;
		value = _mm_add_ps(_mm_add_ps(
			_mm_mul_ps(row_0, _mm_shuffle_ps(d, d, 0x00)),
			_mm_mul_ps(row_1, _mm_shuffle_ps(d, d, 0x55))),
			_mm_mul_ps(row_2, _mm_shuffle_ps(d, d, 0xaa)));
	}
};

// the rows of a transform's rotation, so a direction can be turned back
struct rotation_rows_306400
{
	__m128 rows[3];

	void set_transposed(transform_306400 const *transform)
	{
		__m128 const c0 = transform->columns[0];
		__m128 const c1 = transform->columns[1];
		__m128 const c2 = transform->columns[2];
		__m128 const t0 = _mm_shuffle_ps(c0, c1, 0x44);
		__m128 const t2 = _mm_shuffle_ps(c0, c1, 0xee);
		__m128 const t1 = _mm_shuffle_ps(c2, c2, 0x44);
		__m128 const t3 = _mm_shuffle_ps(c2, c2, 0xee);
		rows[0] = _mm_shuffle_ps(t0, t1, 0x88);
		rows[1] = _mm_shuffle_ps(t0, t1, 0xdd);
		rows[2] = _mm_shuffle_ps(t2, t3, 0x88);
	}
};

class box_pair_306400
{
public:
	char unknown0[0x14];
	transform_306400 const *first_transform;
	transform_306400 const *second_transform;
	char unknown1c[0x54];
	vector_306400 relative[4];
	vector_306400 relative_offset;
	vector_306400 first_centre;

	void function_306400();
};

// @retail 0x306400
void box_pair_306400::function_306400()
{
	rotation_rows_306400 inverse;
	inverse.set_transposed(first_transform);
	__m128 const *column = second_transform->columns;
	vector_306400 *result = relative;
	for (int count = 4; count != 0; count--)
	{
		__m128 const d = *column;
		__m128 const z = _mm_mul_ps(inverse.rows[2], _mm_shuffle_ps(d, d, 0xaa));
		__m128 const y = _mm_mul_ps(inverse.rows[1], _mm_shuffle_ps(d, d, 0x55));
		__m128 const x = _mm_mul_ps(inverse.rows[0], _mm_shuffle_ps(d, d, 0x00));
		result->value = _mm_add_ps(_mm_add_ps(x, y), z);
		result++;
		column++;
	}
	vector_306400 first_position;
	first_position.set_inverse_rotated(first_transform, &first_transform->columns[3]);
	relative_offset.value = relative[3].value;
	relative_offset.value = _mm_sub_ps(relative_offset.value, first_position.value);
	relative[3].value = relative_offset.value;
	first_centre.set_inverse_rotated((transform_306400 const *)relative, &relative_offset.value);
}
