// @flags /O2 /GL- /GX
// Havok (third-party physics library): creating the object kept for a pair of
// convex shapes (constructor 0x2ee2e0), and the queries that pass a pair on
// when the search between its shapes finds them touching.
#include "pair_agent_2ed170.h"
#include "convex_search_3048a0.h"
#include "timer_mark_2ebc80.h"

struct c_query_transform
{
	__m128 axes[3];
	__m128 position;

	void inverse_product(const c_query_transform *a, const c_query_transform *b);
};

class convex_2fefd0
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual long type() const { return 0; }

	long field_4;
	long field_8;
	float radius;
};

struct triangle_2ff0c0;

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

// where a body sits: two vectors, then its transform
struct placement_2ee3f0
{
	__m128 field_0;
	__m128 field_10;
	c_query_transform transform;
};

// one side of a query: a shape, a key, where it sits, and its parent side
struct body_2ee3f0
{
	convex_2fefd0 const *shape;
	long key;
	placement_2ee3f0 const *placement;
	body_2ee3f0 const *parent;
};

// told of each pair found touching
class collector_2ee3f0
{
public:
	virtual void slot_0() {}
	virtual void slot_1(body_2ee3f0 const *a, body_2ee3f0 const *b) {}
};

// the object as its constructor's file declares it, with its full size
class convex_pair_2ee2e0 : public sized_2ed170
{
public:
	pair_state_2fefd0 state;
	char unknown18[0xf0 - 0x18];

	convex_pair_2ee2e0(description_2ed170 const *first, description_2ed170 const *second, long arg_3);
	void function_2ee3f0(body_2ee3f0 const *a, body_2ee3f0 const *b, void const *input, collector_2ee3f0 *collector);
};

// @retail 0x2ee390
void *__cdecl function_2ee390(long arg_0, long arg_1, long arg_2, long value)
{
	return new convex_pair_2ee2e0((description_2ed170 const *)arg_0, (description_2ed170 const *)arg_1, value);
}

// the search run from the pair's kept state; the pair passed on when it
// fails, or when the shapes' radii cover the distance it finds
// @retail 0x2ee3f0
void convex_pair_2ee2e0::function_2ee3f0(body_2ee3f0 const *a, body_2ee3f0 const *b, void const *input, collector_2ee3f0 *collector)
{
	timer_add_2ebc80("TtGsk");
	convex_2fefd0 const *first = a->shape;
	convex_2fefd0 const *second = b->shape;
	c_query_transform transform;
	transform.inverse_product(&a->placement->transform, &b->placement->transform);
	class_3048a0 search;
	search.field_c = true;
	closest_3048a0 closest;
	int status = search.function_3048a0(first, second, &transform, &state, &closest);
	timer_add_2ebc80("Et");
	if (status == 0)
	{
		if (closest.point.m128_f32[3] - first->radius - second->radius < 0.0f)
		{
			collector->slot_1(a, b);
		}
	}
	else
	{
		collector->slot_1(a, b);
	}
}

// the same with a search state started for the pair alone
// @retail 0x2ee500
void __cdecl function_2ee500(void const *a_, void const *b_, void const *input, void *collector_)
{
	body_2ee3f0 const *a = (body_2ee3f0 const *)a_;
	body_2ee3f0 const *b = (body_2ee3f0 const *)b_;
	collector_2ee3f0 *collector = (collector_2ee3f0 *)collector_;
	timer_add_2ebc80("TtGsk");
	convex_2fefd0 const *first = a->shape;
	convex_2fefd0 const *second = b->shape;
	c_query_transform transform;
	transform.inverse_product(&a->placement->transform, &b->placement->transform);
	pair_state_2fefd0 state;
	if (second->type() == 5)
	{
		state.function_2ff0c0(first, (triangle_2ff0c0 const *)second, &transform);
	}
	else
	{
		state.start(first, second, &transform);
	}
	class_3048a0 search;
	search.field_c = true;
	closest_3048a0 closest;
	int status = search.function_3048a0(first, second, &transform, &state, &closest);
	timer_add_2ebc80("Et");
	if (status != 0 || closest.point.m128_f32[3] - first->radius - second->radius < 0.0f)
	{
		collector->slot_1(a, b);
	}
}
