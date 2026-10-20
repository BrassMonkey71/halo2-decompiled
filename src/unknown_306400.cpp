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

static __declspec(align(16)) const unsigned long g_455940[4] = {0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff};

// whether two boxes overlap, returned through a hidden pointer
class answer_306580
{
public:
	answer_306580() {}

	char value;
};

// a vector set from three floats, its last component cleared
struct vector_306580
{
	__m128 value;

	void set(float x, float y, float z)
	{
		float *components = (float *)&value;
		components[0] = x;
		components[1] = y;
		components[2] = z;
		components[3] = 0.0f;
	}
};

// which of x, y and z exceed the value, as bits (src/unknown_305900.cpp)
void __cdecl function_305900(const __m128 *vector, const float *value, int *mask);
// replaces x, y and z with the reciprocals of their square roots
// (src/unknown_305940.cpp)
void __cdecl function_305940(float *vector);
// replaces the components of a vector where another exceeds a value
// (src/unknown_305990.cpp)
void __cdecl function_305990(__m128 *vector, const __m128 *replacement, const __m128 *compare, const __m128 *limit);

// the separation along the cross product of two of the boxes' axes
// (src/unknown_305b30.cpp)
class box_305b30
{
public:
	void function_305b30(__m128 *out, long i, long j) const;
};

// the same comparison as function_305900, written in place
inline void exceeds_306580(const __m128 *vector, const float *value, int *mask)
{
	__m128 limit = _mm_set_ss(*value);
	limit = _mm_shuffle_ps(limit, limit, 0);
	*mask = _mm_movemask_ps(_mm_cmpgt_ps(*vector, limit)) & 7;
}

// two boxes, the second seen from the first, and how far apart they are
// along each of the fifteen axes that can separate them
class class_306580
{
public:
	char unknown0[0x20];
	__m128 first_extents;
	__m128 second_extents;
	char unknown40[0x20];
	float tolerance;
	char unknown64[0xc];
	// the second box's axes in the first box's frame
	__m128 axes[3];
	__m128 unknowna0;
	// the second box's centre in the first box's frame, and the first's in
	// the second's
	__m128 second_centre;
	__m128 first_centre;
	float first_faces[3];
	float second_faces[3];
	float edges[3][3];

	answer_306580 function_306580();
};

// whether the boxes overlap: no face or edge axis separates them by more
// than the tolerance
// @retail 0x306580
answer_306580 class_306580::function_306580()
{
	answer_306580 result;
	__m128 const parallel_limit = _mm_set_ss(999.99994f);
	__m128 const parallel_separation = _mm_set_ss(-1e17f);
	int separated;
	__m128 const mask = *(__m128 const *)g_455940;
	__m128 const a0 = _mm_and_ps(axes[0], mask);
	__m128 const a1 = _mm_and_ps(axes[1], mask);
	__m128 const a2 = _mm_and_ps(axes[2], mask);

	// the first box's faces
	__m128 separation;
	{
		__m128 const second = second_extents;
		__m128 const z = _mm_mul_ps(a2, _mm_shuffle_ps(second, second, 0xaa));
		__m128 const y = _mm_mul_ps(a1, _mm_shuffle_ps(second, second, 0x55));
		__m128 const x = _mm_mul_ps(a0, _mm_shuffle_ps(second, second, 0x00));
		__m128 const reach = _mm_add_ps(_mm_add_ps(_mm_add_ps(x, y), z), first_extents);
		separation = _mm_sub_ps(_mm_and_ps(second_centre, *(__m128 const *)g_455940), reach);
	}
	exceeds_306580(&separation, &tolerance, &separated);
	if (separated)
	{
		result.value = 0;
		return result;
	}
	first_faces[0] = separation.m128_f32[0];
	first_faces[1] = separation.m128_f32[1];
	first_faces[2] = separation.m128_f32[2];

	// the second box's faces
	{
		__m128 const t0 = _mm_shuffle_ps(a0, a1, 0x44);
		__m128 const t2 = _mm_shuffle_ps(a0, a1, 0xee);
		__m128 const t1 = _mm_shuffle_ps(a2, a2, 0x44);
		__m128 const t3 = _mm_shuffle_ps(a2, a2, 0xee);
		__m128 const row_0 = _mm_shuffle_ps(t0, t1, 0x88);
		__m128 const row_1 = _mm_shuffle_ps(t0, t1, 0xdd);
		__m128 const row_2 = _mm_shuffle_ps(t2, t3, 0x88);
		__m128 const first = first_extents;
		__m128 const z = _mm_mul_ps(row_2, _mm_shuffle_ps(first, first, 0xaa));
		__m128 const y = _mm_mul_ps(row_1, _mm_shuffle_ps(first, first, 0x55));
		__m128 const x = _mm_mul_ps(row_0, _mm_shuffle_ps(first, first, 0x00));
		__m128 const reach = _mm_add_ps(_mm_add_ps(_mm_add_ps(x, y), z), second_extents);
		separation = _mm_sub_ps(_mm_and_ps(first_centre, *(__m128 const *)g_455940), reach);
	}
	exceeds_306580(&separation, &tolerance, &separated);
	if (separated)
	{
		result.value = 0;
		return result;
	}
	second_faces[0] = separation.m128_f32[0];
	second_faces[1] = separation.m128_f32[1];
	second_faces[2] = separation.m128_f32[2];

	// the edges: the squares of each row of the axes, for the lengths of
	// the cross products
	vector_306580 squares_x;
	squares_x.set(axes[0].m128_f32[0], axes[1].m128_f32[0], axes[2].m128_f32[0]);
	squares_x.value = _mm_mul_ps(squares_x.value, squares_x.value);
	vector_306580 squares_y;
	squares_y.set(axes[0].m128_f32[1], axes[1].m128_f32[1], axes[2].m128_f32[1]);
	squares_y.value = _mm_mul_ps(squares_y.value, squares_y.value);
	vector_306580 squares_z;
	squares_z.set(axes[0].m128_f32[2], axes[1].m128_f32[2], axes[2].m128_f32[2]);
	squares_z.value = _mm_mul_ps(squares_z.value, squares_z.value);
	vector_306580 reach;
	__m128 lengths;
	__m128 edge;

	// the first box's x axis across each of the second's
	((box_305b30 const *)this)->function_305b30(&edge, 1, 2);
	reach.set(a0.m128_f32[2] * first_extents.m128_f32[1] + a0.m128_f32[1] * first_extents.m128_f32[2] + a1.m128_f32[0] * second_extents.m128_f32[2] + a2.m128_f32[0] * second_extents.m128_f32[1],
		a1.m128_f32[2] * first_extents.m128_f32[1] + a1.m128_f32[1] * first_extents.m128_f32[2] + a2.m128_f32[0] * second_extents.m128_f32[0] + a0.m128_f32[0] * second_extents.m128_f32[2],
		a2.m128_f32[2] * first_extents.m128_f32[1] + a2.m128_f32[1] * first_extents.m128_f32[2] + a1.m128_f32[0] * second_extents.m128_f32[0] + a0.m128_f32[0] * second_extents.m128_f32[1]);
	lengths = _mm_add_ps(squares_z.value, squares_y.value);
	function_305940((float *)&lengths);
	edge = _mm_mul_ps(lengths, _mm_sub_ps(edge, reach.value));
	exceeds_306580(&edge, &tolerance, &separated);
	if (separated)
	{
		result.value = 0;
		return result;
	}
	function_305990(&edge, &parallel_separation, &lengths, &parallel_limit);
	edges[0][0] = edge.m128_f32[0];
	edges[1][0] = edge.m128_f32[1];
	edges[2][0] = edge.m128_f32[2];

	// the first box's y axis across each of the second's
	((box_305b30 const *)this)->function_305b30(&edge, 2, 0);
	reach.set(a1.m128_f32[1] * second_extents.m128_f32[2] + a0.m128_f32[0] * first_extents.m128_f32[2] + a0.m128_f32[2] * first_extents.m128_f32[0] + a2.m128_f32[1] * second_extents.m128_f32[1],
		a0.m128_f32[1] * second_extents.m128_f32[2] + a2.m128_f32[1] * second_extents.m128_f32[0] + a1.m128_f32[0] * first_extents.m128_f32[2] + a1.m128_f32[2] * first_extents.m128_f32[0],
		a1.m128_f32[1] * second_extents.m128_f32[0] + a2.m128_f32[0] * first_extents.m128_f32[2] + a0.m128_f32[1] * second_extents.m128_f32[1] + a2.m128_f32[2] * first_extents.m128_f32[0]);
	lengths = _mm_add_ps(squares_z.value, squares_x.value);
	function_305940((float *)&lengths);
	edge = _mm_mul_ps(lengths, _mm_sub_ps(edge, reach.value));
	exceeds_306580(&edge, &tolerance, &separated);
	if (separated)
	{
		result.value = 0;
		return result;
	}
	function_305990(&edge, &parallel_separation, &lengths, &parallel_limit);
	edges[0][1] = edge.m128_f32[0];
	edges[1][1] = edge.m128_f32[1];
	edges[2][1] = edge.m128_f32[2];

	// the first box's z axis across each of the second's
	((box_305b30 const *)this)->function_305b30(&edge, 0, 1);
	reach.set(a1.m128_f32[2] * second_extents.m128_f32[2] + a0.m128_f32[0] * first_extents.m128_f32[1] + a0.m128_f32[1] * first_extents.m128_f32[0] + a2.m128_f32[2] * second_extents.m128_f32[1],
		a0.m128_f32[2] * second_extents.m128_f32[2] + a2.m128_f32[2] * second_extents.m128_f32[0] + a1.m128_f32[0] * first_extents.m128_f32[1] + a1.m128_f32[1] * first_extents.m128_f32[0],
		a1.m128_f32[2] * second_extents.m128_f32[0] + a2.m128_f32[0] * first_extents.m128_f32[1] + a0.m128_f32[2] * second_extents.m128_f32[1] + a2.m128_f32[1] * first_extents.m128_f32[0]);
	lengths = _mm_add_ps(squares_y.value, squares_x.value);
	function_305940((float *)&lengths);
	edge = _mm_mul_ps(lengths, _mm_sub_ps(edge, reach.value));
	function_305900(&edge, &tolerance, &separated);
	if (separated)
	{
		result.value = 0;
		return result;
	}
	function_305990(&edge, &parallel_separation, &lengths, &parallel_limit);
	edges[0][2] = edge.m128_f32[0];
	edges[1][2] = edge.m128_f32[1];
	edges[2][2] = edge.m128_f32[2];
	result.value = 1;
	return result;
}
