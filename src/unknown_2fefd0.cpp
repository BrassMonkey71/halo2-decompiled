// @flags /O2 /GL-
// Havok (third-party physics library): starting a pair's search state: the
// first object's support vertex towards the second's centre, and the
// second's support vertex back towards that vertex, in the second's frame.
#include <xmmintrin.h>

// the sign bit, in four lanes
__declspec(align(16)) static const unsigned long sign_mask_4124a0[4] = {
	0x80000000, 0x80000000, 0x80000000, 0x80000000
};

struct c_query_transform
{
	__m128 axes[3];
	__m128 position;
};

struct c_transformed_point
{
	__m128 value;
	void transform(const void *matrix, const __m128 *point);
};

struct vector_2da6e0
{
	__m128 value;
	void inverse_rotate(const c_query_transform *matrix, const __m128 *direction);
};

// a point whose fourth lane holds the vertex's id in its low half
union support_2fefd0
{
	__m128 point;
	struct
	{
		float xyz[3];
		unsigned short id;
	} vertex;
};

class convex_2fefd0
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual void slot_5() {}
	virtual void slot_6() {}
	virtual void slot_7() {}
	virtual void slot_8() {}
	virtual void slot_9() {}
	virtual void slot_10() {}
	virtual void slot_11() {}
	virtual void support(__m128 const *direction, support_2fefd0 *out) const {}
	virtual void slot_13() {}
	virtual void centre(__m128 *out) const {}
	virtual bool slot_15() const { return false; }
};

// a triangle: three corners after a 16-byte header
struct triangle_2ff0c0
{
	char unknown0[0x10];
	__m128 corners[3];
};

// a point placed by a transform
struct placed_point_2ff0c0
{
	__m128 value;

	void set_transformed(c_query_transform const *transform, __m128 const *point)
	{
		__m128 p = *point;
		__m128 z = _mm_add_ps(_mm_mul_ps(transform->axes[2], _mm_shuffle_ps(p, p, 0xaa)), transform->position);
		__m128 y = _mm_mul_ps(transform->axes[1], _mm_shuffle_ps(p, p, 0x55));
		__m128 x = _mm_mul_ps(transform->axes[0], _mm_shuffle_ps(p, p, 0x00));
		value = _mm_add_ps(_mm_add_ps(x, y), z);
	}
};

// the cross product of two vectors' first three terms
inline __m128 cross_2ff0c0(__m128 const &a, __m128 const &b)
{
	return _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(a, a, 0xc9), _mm_shuffle_ps(b, b, 0xd2)),
		_mm_mul_ps(_mm_shuffle_ps(a, a, 0xd2), _mm_shuffle_ps(b, b, 0xc9)));
}

struct pair_state_2fefd0
{
	unsigned short first_id;
	unsigned short second_id;
	unsigned short field_4;
	unsigned short field_6;
	bool field_8;
	unsigned char field_9;
	bool first_flag;
	unsigned char second_flag;

	void start(convex_2fefd0 const *first, convex_2fefd0 const *second, c_query_transform const *transform);
	void function_2ff0c0(convex_2fefd0 const *first, triangle_2ff0c0 const *triangle, c_query_transform const *transform);
};

// @retail 0x2fefd0
void pair_state_2fefd0::start(convex_2fefd0 const *first, convex_2fefd0 const *second, c_query_transform const *transform)
{
	__m128 first_centre;
	first->centre(&first_centre);
	__m128 second_centre;
	second->centre(&second_centre);
	c_transformed_point second_world;
	second_world.transform(transform, &second_centre);
	__m128 direction = _mm_sub_ps(second_world.value, first_centre);
	support_2fefd0 first_vertex;
	first->support(&direction, &first_vertex);
	first_id = first_vertex.vertex.id;
	direction = _mm_sub_ps(second_world.value, first_vertex.point);
	vector_2da6e0 local;
	local.inverse_rotate(transform, &direction);
	local.value = _mm_xor_ps(local.value, *(__m128 const *)sign_mask_4124a0);
	support_2fefd0 second_vertex;
	second->support(&local.value, &second_vertex);
	second_id = second_vertex.vertex.id;
	field_4 = 0xffff;
	field_6 = 0xffff;
	field_8 = true;
	field_9 = true;
	first_flag = first->slot_15();
	second_flag = second->slot_15();
}

// starting the search state of an object and a triangle: the triangle's
// corners placed by the transform, its normal turned to face away from the
// object's centre, and the object's support vertex against that normal
// @retail 0x2ff0c0
void pair_state_2fefd0::function_2ff0c0(convex_2fefd0 const *first, triangle_2ff0c0 const *triangle, c_query_transform const *transform)
{
	second_id = 0;
	field_4 = 0x10;
	field_6 = 0x20;
	placed_point_2ff0c0 corners[3];
	__m128 const *corner = triangle->corners;
	placed_point_2ff0c0 *placed = corners;
	for (int count = 3; count != 0; count--)
	{
		placed->set_transformed(transform, corner);
		placed++;
		corner++;
	}
	__m128 normal = cross_2ff0c0(_mm_sub_ps(corners[1].value, corners[0].value), _mm_sub_ps(corners[2].value, corners[1].value));

	__m128 centre;
	first->centre(&centre);
	__m128 const product = _mm_mul_ps(_mm_sub_ps(centre, corners[0].value), normal);
	if (_mm_movemask_ps(_mm_add_ss(_mm_shuffle_ps(product, product, 0xaa), _mm_add_ss(_mm_shuffle_ps(product, product, 0x55), product))) & 1)
	{
		normal = _mm_xor_ps(normal, *(__m128 const *)sign_mask_4124a0);
	}
	support_2fefd0 vertex;
	first->support(&normal, &vertex);
	first_id = vertex.vertex.id;
	field_8 = true;
	field_9 = 3;
	first_flag = first->slot_15();
	second_flag = 3;
}
