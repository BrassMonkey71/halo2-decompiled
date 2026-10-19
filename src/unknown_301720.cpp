// @flags /O2 /GL-
// Havok (third-party physics library): starting a ray cast over a tree in
// fixed-point coordinates, either giving back whether it hit or reporting
// what it hits through a callback.
#include <xmmintrin.h>

struct s_244980_ray;
struct s_244980_output;
class c_244c10;

// the tree's origin, with the size of one unit as the fourth term, and the
// tree itself at 0x30
struct tree_301800
{
	__m128 origin;
	char unknown10[0x20];
	char root[1];
};

struct ray_301800
{
	__m128 from;
	__m128 to;
	long field_20;
	long field_24;
};

// whether a cast hit, given back by value
struct result_2df6e0
{
	result_2df6e0() {}

	bool hit;
};

struct callback_301800
{
	long field_0;
	long field_4;
};

// the nodes still to visit
struct pending_301800
{
	__m128 offset;
	long field_10;
	float scale;
	long field_18;
	long field_1c;
};

// the ray's two ends in the tree's fixed-point units
struct fixed_ray_301800
{
	__m128 from;
	__m128 to;
};

struct class_2df670
{
	char unknown0[0x10];
	tree_301800 const *tree;
	float inverse_scale;
	char unknown18[8];
	ray_301800 ray;
	bool hit;
	union
	{
		long field_54;
		float fraction;
	};
	long field_58;
	c_244c10 *callback;
	s_244980_output *output;
	void const *shape;

	result_2df6e0 function_301720(void const *shape, void const *tree, void const *ray, void *output);
	void function_301800(void const *shape, void const *tree, s_244980_ray const *ray, s_244980_output *output, c_244c10 *callback);
	void function_3009e0(pending_301800 *pending, void const *root, fixed_ray_301800 const *ray);
};

// a vector of four copies of a float
inline __m128 splat_301720(float value)
{
	__m128 const single = _mm_set_ss(value);
	return _mm_shuffle_ps(single, single, 0);
}

// the cast run with its closest hit so far at the far end; whether it hit
// @retail 0x301720
result_2df6e0 class_2df670::function_301720(void const *shape_, void const *tree_, void const *ray_, void *output_)
{
	shape = shape_;
	tree_301800 const *source = (tree_301800 const *)tree_;
	tree = source;
	field_58 = (long)output_;
	fraction = 1.0f;
	pending_301800 pending;
	pending.offset = _mm_setzero_ps();
	inverse_scale = 1.0f / source->origin.m128_f32[3];
	float const scale = source->origin.m128_f32[3] * (1.0f / 65536.0f);
	pending.scale = scale;
	ray_301800 const *input = (ray_301800 const *)ray_;
	fixed_ray_301800 fixed;
	__m128 const to = _mm_sub_ps(input->to, source->origin);
	__m128 const from = _mm_sub_ps(input->from, source->origin);
	fixed.from = _mm_mul_ps(splat_301720(scale), from);
	ray.from = input->from;
	fixed.to = _mm_mul_ps(splat_301720(scale), to);
	ray.to = input->to;
	ray.field_20 = input->field_20;
	ray.field_24 = input->field_24;
	hit = false;
	pending.field_18 = 0;
	pending.field_10 = 0;
	pending.field_1c = 0;
	function_3009e0(&pending, source->root, &fixed);
	result_2df6e0 result;
	result.hit = hit;
	return result;
}

// @retail 0x301800
void class_2df670::function_301800(void const *shape_, void const *tree_, s_244980_ray const *ray_, s_244980_output *output_, c_244c10 *callback_)
{
	shape = shape_;
	output = output_;
	callback = callback_;
	field_58 = 0;
	field_54 = ((callback_301800 const *)callback_)->field_4;
	tree_301800 const *source = (tree_301800 const *)tree_;
	tree = source;
	pending_301800 pending;
	pending.offset = _mm_setzero_ps();
	inverse_scale = 1.0f / source->origin.m128_f32[3];
	float const scale = source->origin.m128_f32[3] * (1.0f / 65536.0f);
	pending.scale = scale;
	ray_301800 const *input = (ray_301800 const *)ray_;
	fixed_ray_301800 fixed;
	__m128 const to = _mm_sub_ps(input->to, source->origin);
	__m128 const from = _mm_sub_ps(input->from, source->origin);
	__m128 const single = _mm_load_ss(&scale);
	fixed.from = _mm_mul_ps(_mm_shuffle_ps(single, single, 0), from);
	fixed.to = _mm_mul_ps(_mm_shuffle_ps(single, single, 0), to);
	ray.from = input->from;
	ray.to = input->to;
	ray.field_20 = input->field_20;
	ray.field_24 = input->field_24;
	hit = false;
	pending.field_18 = 0;
	pending.field_10 = 0;
	pending.field_1c = 0;
	function_3009e0(&pending, source->root, &fixed);
}
