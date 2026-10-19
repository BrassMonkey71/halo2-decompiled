// @flags /O2 /GL-
// Havok (third-party physics library): a shape of several rays against a
// convex shape, bracketed by two marks in the timing stream: each ray is
// carried into the convex shape's frame and cast against it; each hit is
// reported as a contact: the hit point and normal in world space, and the
// distance back along the ray.
#include "timer_mark_2ebc80.h"
#include <xmmintrin.h>

static __declspec(align(16)) const float g_412420[4] = {1.0f, 1.0f, 1.0f, 1.0f};

struct c_query_transform
{
	__m128 axes[3];
	__m128 position;

	void inverse_product(const c_query_transform *a, const c_query_transform *b);
};

// a ray: its start, with its length in the fourth lane, and its end
struct ray_2f89b0
{
	__m128 start;
	__m128 end;
};

struct rays_shape_2f89b0
{
	char unknown0[0x10];
	ray_2f89b0 const *rays;
	int ray_count;
};

struct ray_input_2f89b0
{
	__m128 from;
	__m128 to;
	long field_20;
	long field_24;
};

struct ray_output_2f89b0
{
	__m128 normal;
	float field_10;
	float fraction;
	char unknown18[8];
};

struct hit_2f89b0
{
	bool value;
};

class convex_2f89b0
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
	virtual hit_2f89b0 cast_ray(ray_input_2f89b0 const *input, ray_output_2f89b0 *output) const { hit_2f89b0 hit = {false}; return hit; }
};

struct motion_2f89b0
{
	char unknown0[0x20];
	c_query_transform transform;
};

struct body_2f89b0
{
	void const *shape;
	long key;
	motion_2f89b0 const *motion;
};

struct contact_2f89b0
{
	union
	{
		__m128 position;
		float position_and_distance[4];
	};
	__m128 normal;
	body_2f89b0 const *first;
	body_2f89b0 const *second;
};

class collector_2f89b0
{
public:
	virtual void slot_0() {}
	virtual void add_contact(contact_2f89b0 const *contact) {}
};

// a point placed by a transform
inline __m128 transformed_2f89b0(c_query_transform const *transform, __m128 const &p)
{
	__m128 z = _mm_add_ps(_mm_mul_ps(transform->axes[2], _mm_shuffle_ps(p, p, 0xaa)), transform->position);
	__m128 y = _mm_mul_ps(transform->axes[1], _mm_shuffle_ps(p, p, 0x55));
	__m128 x = _mm_mul_ps(transform->axes[0], _mm_shuffle_ps(p, p, 0x00));
	return _mm_add_ps(_mm_add_ps(x, y), z);
}

// a direction turned by a transform
inline __m128 rotated_2f89b0(c_query_transform const *transform, __m128 const &v)
{
	__m128 z = _mm_mul_ps(transform->axes[2], _mm_shuffle_ps(v, v, 0xaa));
	__m128 y = _mm_mul_ps(transform->axes[1], _mm_shuffle_ps(v, v, 0x55));
	__m128 x = _mm_mul_ps(transform->axes[0], _mm_shuffle_ps(v, v, 0x00));
	return _mm_add_ps(_mm_add_ps(x, y), z);
}

class rays_convex_2f89b0
{
public:
	void function_2f89b0(body_2f89b0 const *a, body_2f89b0 const *b, void const *input, collector_2f89b0 *collector);
};

// @retail 0x2f89b0
void rays_convex_2f89b0::function_2f89b0(body_2f89b0 const *a, body_2f89b0 const *b, void const *input, collector_2f89b0 *collector)
{
	timer_add_2ebc80("TtmultiRay-cvx");
	rays_shape_2f89b0 const *rays = (rays_shape_2f89b0 const *)a->shape;
	convex_2f89b0 const *convex = (convex_2f89b0 const *)b->shape;
	ray_output_2f89b0 output;
	c_query_transform transform;
	transform.inverse_product(&b->motion->transform, &a->motion->transform);
	contact_2f89b0 contact;
	ray_input_2f89b0 ray;
	contact.first = a;
	contact.second = b;
	ray.field_24 = 0;
	ray_2f89b0 const *each = rays->rays;
	for (int i = rays->ray_count; i > 0; i--)
	{
		ray.from = transformed_2f89b0(&transform, each->start);
		ray.to = transformed_2f89b0(&transform, each->end);
		output.fraction = 1.0f;
		hit_2f89b0 hit = convex->cast_ray(&ray, &output);
		if (hit.value)
		{
			float fraction = output.fraction;
			float distance = output.fraction - 1.0f;
			__m128 f = _mm_set1_ps(fraction);
			__m128 point = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(*(__m128 const *)g_412420, f), ray.from), _mm_mul_ps(f, ray.to));
			c_query_transform const *world = &b->motion->transform;
			contact.position = transformed_2f89b0(world, point);
			contact.position_and_distance[3] = distance * ((float const *)&each->start)[3];
			contact.normal = rotated_2f89b0(world, output.normal);
			collector->add_contact(&contact);
		}
		each++;
	}
	timer_add_2ebc80("Et");
}
