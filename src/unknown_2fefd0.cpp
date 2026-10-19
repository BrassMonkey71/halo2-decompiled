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

struct pair_state_2fefd0
{
	unsigned short first_id;
	unsigned short second_id;
	unsigned short field_4;
	unsigned short field_6;
	bool field_8;
	bool field_9;
	bool first_flag;
	bool second_flag;

	void start(convex_2fefd0 const *first, convex_2fefd0 const *second, c_query_transform const *transform);
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
