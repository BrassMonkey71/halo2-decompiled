// @flags /O2 /GL- /GX
// Havok (third-party physics library): creating the object kept for a pair of
// convex shapes (constructor 0x2ee2e0), and the queries that pass a pair on
// when the search between its shapes finds them touching, or pass on the
// contact it finds.
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

struct contact_3032c0;

// the result of a query of the pair kept for later: the contact as the search
// gives it, then its point in the second shape's frame and its normal in the
// world
struct kept_contact_2ee610;

// whether a query found a contact
struct found_2ee610
{
	bool value;

	found_2ee610(bool value_)
	{
		value = value_;
	}
};

// the object as its constructor's file declares it, with its full size: its
// search state, and the last separating direction with a distance in its
// fourth lane that the shapes' motion must use up before they can touch
class convex_pair_2ee2e0 : public sized_2ed170
{
public:
	pair_state_2fefd0 state;
	long field_18;
	char unknown1c[0x20 - 0x1c];
	__m128 separation;
	char unknown30[0xf0 - 0x30];

	convex_pair_2ee2e0(description_2ed170 const *first, description_2ed170 const *second, long arg_3);
	void function_2ee3f0(body_2ee3f0 const *a, body_2ee3f0 const *b, void const *input, collector_2ee3f0 *collector);
	found_2ee610 function_2ee610(body_2ee3f0 const *a, body_2ee3f0 const *b, void const *input, kept_contact_2ee610 *out);
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

// a direction turned by a transform (0x2da6e0)
struct vector_2da6e0
{
	__m128 value;
	void rotate(const c_query_transform *matrix, const __m128 *direction);
};

// the closest points as the search finds them: a plane through the second
// shape's point, and the contact made from it (0x3032c0)
struct plane_3032c0;

struct contact_3032c0
{
	__m128 normal;
	__m128 point;
	float distance;
	float weight;
};

class source_3032c0
{
public:
	void function_3032c0(void *unused, plane_3032c0 *plane, contact_3032c0 *out) const;
};

// a contact passed to the collector: its point, with the separation in the
// fourth lane, its normal, and the two sides
struct contact_2ee8b0
{
	__m128 point;
	__m128 normal;
	body_2ee3f0 const *a;
	body_2ee3f0 const *b;
};

class contact_collector_2ee8b0
{
public:
	virtual void slot_0() {}
	virtual void add_contact(contact_2ee8b0 const *contact) {}
};

struct input_2ee8b0
{
	long field_0;
	long field_4;
	float tolerance;
};

// a vector of four copies of a float
inline __m128 splat_2ee8b0(float value)
{
	__m128 const single = _mm_set_ss(value);
	return _mm_shuffle_ps(single, single, 0);
}

// a point taken into a transform's frame (0x2da660, inlined here)
struct local_point_2ee8b0
{
	__m128 value;

	__forceinline void inverse_transform(c_query_transform const *matrix, __m128 const &point)
	{
		__m128 d = _mm_sub_ps(point, matrix->position);
		__m128 c0 = matrix->axes[0];
		__m128 c1 = matrix->axes[1];
		__m128 c2 = matrix->axes[2];
		__m128 t0 = _mm_shuffle_ps(c0, c1, 0x44);
		__m128 t2 = _mm_shuffle_ps(c0, c1, 0xee);
		__m128 t1 = _mm_shuffle_ps(c2, c2, 0x44);
		__m128 t3 = _mm_shuffle_ps(c2, c2, 0xee);
		__m128 row_0 = _mm_shuffle_ps(t0, t1, 0x88);
		__m128 row_1 = _mm_shuffle_ps(t0, t1, 0xdd);
		__m128 r2 = _mm_shuffle_ps(t2, t3, 0x88);
		value = _mm_add_ps(_mm_add_ps(
			_mm_mul_ps(row_0, _mm_shuffle_ps(d, d, 0x00)),
			_mm_mul_ps(row_1, _mm_shuffle_ps(d, d, 0x55))),
			_mm_mul_ps(r2, _mm_shuffle_ps(d, d, 0xaa)));
	}
};

// a point placed by a transform (0x2da610, inlined here)
__forceinline __m128 transform_2ee8b0(c_query_transform const *m, __m128 const &p)
{
	__m128 z = _mm_add_ps(_mm_mul_ps(m->axes[2], _mm_shuffle_ps(p, p, 0xaa)), m->position);
	__m128 y = _mm_mul_ps(m->axes[1], _mm_shuffle_ps(p, p, 0x55));
	__m128 x = _mm_mul_ps(m->axes[0], _mm_shuffle_ps(p, p, 0x00));
	return _mm_add_ps(_mm_add_ps(x, y), z);
}

struct kept_contact_2ee610
{
	contact_3032c0 found;
	__m128 local_point;
	vector_2da6e0 normal;
};

struct motion_input_2ee610
{
	long field_0;
	long field_4;
	float tolerance;
	bool const *keep_separation;
};

// the closest points of the pair's two convex shapes for later use, skipped
// while the shapes' motion since the last query cannot have used up the
// distance they were apart: the search's contact, its normal in the world,
// and its point taken onto the second shape's surface in that shape's frame;
// a miss may keep the separating direction for next time
// @retail 0x2ee610
found_2ee610 convex_pair_2ee2e0::function_2ee610(body_2ee3f0 const *a, body_2ee3f0 const *b, void const *input_, kept_contact_2ee610 *out)
{
	motion_input_2ee610 const *input = (motion_input_2ee610 const *)input_;
	convex_2fefd0 const *first = a->shape;
	convex_2fefd0 const *second = b->shape;
	if (separation.m128_f32[3] > 0.0f)
	{
		timer_add_2ebc80("StTim");
		placement_2ee3f0 const *from = a->placement;
		placement_2ee3f0 const *to = b->placement;
		__m128 const moved = _mm_mul_ps(_mm_sub_ps(_mm_sub_ps(to->field_10, to->field_0), _mm_sub_ps(from->field_10, from->field_0)), separation);
		float along;
		_mm_store_ss(&along, _mm_add_ss(_mm_shuffle_ps(moved, moved, 0xaa), _mm_add_ss(_mm_shuffle_ps(moved, moved, 0x55), moved)));
		separation.m128_f32[3] -= to->field_0.m128_f32[3] + from->field_0.m128_f32[3] + along;
		if (separation.m128_f32[3] > 0.0f)
		{
			return found_2ee610(false);
		}
	}
	timer_add_2ebc80("StGsk");
	c_query_transform transform;
	transform.inverse_product(&a->placement->transform, &b->placement->transform);
	class_3048a0 search;
	search.field_c = false;
	closest_3048a0 closest;
	if (search.function_3048a0(first, second, &transform, &state, &closest) != 0)
	{
		return found_2ee610(false);
	}
	((source_3032c0 const *)&search)->function_3032c0(&state, (plane_3032c0 *)&closest, &out->found);
	vector_2da6e0 *normal = &out->normal;
	normal->rotate(&a->placement->transform, &out->found.normal);
	float const distance = out->found.distance - first->radius - second->radius;
	out->found.distance = distance;
	if (distance < input->tolerance)
	{
		out->found.point = _mm_add_ps(out->found.point, _mm_mul_ps(splat_2ee8b0(-first->radius), out->found.normal));
		__m128 const surface = _mm_add_ps(out->found.point, _mm_mul_ps(splat_2ee8b0(-distance), out->found.normal));
		local_point_2ee8b0 local;
		local.inverse_transform(&transform, surface);
		out->local_point = local.value;
		return found_2ee610(true);
	}
	if (field_18 == 0 && *input->keep_separation)
	{
		separation = normal->value;
		separation.m128_f32[3] = distance - input->tolerance * 1.1f;
	}
	return found_2ee610(false);
}
// the contact of two convex shapes, with a search state started for the
// pair alone: the closest points the search finds, taken onto the shapes'
// surfaces, passed on when they are within the tolerance
// @retail 0x2ee8b0
void __cdecl function_2ee8b0(void const *a_, void const *b_, void const *input, void *collector)
{
	timer_add_2ebc80("LtGsk");
	body_2ee3f0 const *a = (body_2ee3f0 const *)a_;
	body_2ee3f0 const *b = (body_2ee3f0 const *)b_;
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
	first = a->shape;
	second = b->shape;
	class_3048a0 search;
	search.field_c = false;
	closest_3048a0 closest;
	if (search.function_3048a0(first, second, &transform, &state, &closest) == 0)
	{
		contact_3032c0 found;
		((source_3032c0 const *)&search)->function_3032c0(&state, (plane_3032c0 *)&closest, &found);
		vector_2da6e0 normal;
		normal.rotate(&a->placement->transform, &found.normal);
		found.distance = found.distance - first->radius - second->radius;
		float const distance = found.distance;
		if (distance < ((input_2ee8b0 const *)input)->tolerance)
		{
			found.point = _mm_add_ps(found.point, _mm_mul_ps(splat_2ee8b0(-first->radius), found.normal));
			__m128 const surface = _mm_add_ps(found.point, _mm_mul_ps(splat_2ee8b0(-distance), found.normal));
			local_point_2ee8b0 local;
			local.inverse_transform(&transform, surface);
			contact_2ee8b0 contact;
			contact.a = a;
			contact.b = b;
			contact.point = transform_2ee8b0(&b->placement->transform, local.value);
			contact.point.m128_f32[3] = distance;
			contact.normal = normal.value;
			((contact_collector_2ee8b0 *)collector)->add_contact(&contact);
		}
	}
	timer_add_2ebc80("lt");
}
