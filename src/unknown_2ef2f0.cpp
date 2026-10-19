// @flags /O2 /GL- /GX
// Havok (third-party physics library): the object kept for a pair of small
// shapes, holding a manifold of up to eight contacts, and its query that
// grows both shapes by their radii.
#include "pair_agent_2ed170.h"
#include "timer_mark_2ebc80.h"

struct s_308180_entry
{
	unsigned short first;
	unsigned short second;
	unsigned short field_4;
};

// a manifold of up to eight contacts
class class_308180
{
public:
	char unknown0[0x20];
	s_308180_entry entries[8];
	long field_50;
	int count;
	bool changed;

	class_308180();
};

// a query's input (constructor 0x2ef260)
class query_2ef260
{
public:
	long field_0;
	long field_4;
	long field_8;
	long field_c;
	long field_10;
	long field_14;
	long field_18;
	__m128 from;
	__m128 to;
	__m128 grown_from;
	__m128 grown_to;
	float radius;
	float tolerance;
	char unknown68[0x110 - 0x68];

	query_2ef260(long a, long b, long c, long d, long e, long f, __m128 const &from_, long g, __m128 const &to_, float radius_);
	void function_3080a0(class_308180 *manifold);
};

// a box: a radius it is grown by, and its half extents
struct box_2ef3b0
{
	char unknown0[0xc];
	float radius;
	__m128 half_extents;
};

struct input_2ef2f0
{
	long field_0;
	long field_4;
	float tolerance;
};

class manifold_pair_2ef2f0 : public sized_2ed170
{
public:
	long field_c;
	class_308180 manifold;
	long field_6c;

	__forceinline manifold_pair_2ef2f0(long value) : sized_2ed170(value) {}

	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void function_2ef3b0(description_2ed170 const *a, description_2ed170 const *b, input_2ef2f0 const *input, long arg_3);
};

void *__cdecl function_2ee390(long arg_0, long arg_1, long arg_2, long value);

// the manifold object when both boxes are large against the tolerance, the
// general object otherwise
// @retail 0x2ef2f0
void *__cdecl function_2ef2f0(long arg_0, long arg_1, long arg_2, long value)
{
	description_2ed170 const *a = (description_2ed170 const *)arg_0;
	description_2ed170 const *b = (description_2ed170 const *)arg_1;
	input_2ef2f0 const *input = (input_2ef2f0 const *)arg_2;
	box_2ef3b0 const *first_box = (box_2ef3b0 const *)a->shape;
	box_2ef3b0 const *second_box = (box_2ef3b0 const *)b->shape;
	if (!(first_box->half_extents.m128_f32[3] * 1.999f <= input->tolerance) &&
		!(second_box->half_extents.m128_f32[3] * 1.999f <= input->tolerance))
	{
		return new manifold_pair_2ef2f0(value);
	}
	return function_2ee390(arg_0, arg_1, arg_2, value);
}

// @retail 0x2ef3b0
void manifold_pair_2ef2f0::function_2ef3b0(description_2ed170 const *a, description_2ed170 const *b, input_2ef2f0 const *input, long arg_3)
{
	timer_add_2ebc80("TtBoxBox");
	box_2ef3b0 const *first_box = (box_2ef3b0 const *)a->shape;
	box_2ef3b0 const *second_box = (box_2ef3b0 const *)b->shape;
	__m128 from = _mm_add_ps(first_box->half_extents, _mm_set_ps1(first_box->radius));
	__m128 to = _mm_add_ps(second_box->half_extents, _mm_set_ps1(second_box->radius));
	query_2ef260 query((long)a, (long)b, (long)input, field_8, arg_3, (long)a->placement + 0x20, from,
		(long)b->placement + 0x20, to, input->tolerance);
	query.function_3080a0(&manifold);
	timer_add_2ebc80("Et");
}
