// @flags /O2 /GL-
// Havok (third-party physics library): casting a ray over a tree stored as a
// command stream in fixed-point coordinates (0x3009e0), and starting such a
// cast, either giving back whether it hit or reporting what it hits through a
// callback (0x301720, 0x301800).
#include <xmmintrin.h>
#include "stream_holder_2d8e70.h"

struct s_244980_ray;
struct s_244980_output;
class c_244c10;

// what reports a stream's errors: its second slot gives the stream to write
// the message to, which also ends the report (src/unknown_2fefd0.cpp)
class reporter_2ff210
{
public:
	virtual void slot_0() {}
	virtual stream_holder_2d8e70 *slot_1() { return 0; }
};

extern reporter_2ff210 *g_48017c;

struct class_2d9060
{
	long function_2d9060();
};

static __declspec(align(16)) const float g_412420[4] = {1.0f, 1.0f, 1.0f, 1.0f};

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
	class filter_3009e0 *filter;
};

// whether a cast hit, given back by value
struct result_2df6e0
{
	result_2df6e0() {}

	bool hit;
};

// whether a test passed, given back by value
struct answer_3009e0
{
	answer_3009e0() {}

	bool value;
};

// what decides whether a leaf is cast against
class filter_3009e0
{
public:
	virtual answer_3009e0 slot_0(ray_301800 const *ray, void const *shape, long key) = 0;
};

struct callback_301800
{
	long field_0;
	long field_4;
};

// where the closest hit so far is kept
struct closest_3009e0
{
	char unknown0[0x10];
	long key;
	long fraction;
};

// a leaf's shape as the cast sees it
class leaf_3009e0
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
	virtual answer_3009e0 cast_closest(ray_301800 const *ray, closest_3009e0 *closest) = 0;
	virtual void cast_reporting(ray_301800 const *ray, void const *hit_info, c_244c10 *callback) = 0;
};

// the shape the tree's leaves belong to: its slot 13 gives a leaf's shape
class shape_3009e0
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
	virtual void slot_12() {}
	virtual leaf_3009e0 *leaf_at_key(long key, void *buffer) = 0;
};

// what a reporting cast passes on with a leaf
struct hit_info_3009e0
{
	leaf_3009e0 *leaf;
	long key;
	long field_8;
	s_244980_output *output;
};

// the nodes still to visit: the offset of the tree's fixed point, the depth,
// the size of one unit, the base of the leaves' keys, and a value the commands
// set
struct pending_301800
{
	__m128 offset;
	long depth;
	float scale;
	long key_base;
	long values[1];
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
	closest_3009e0 *closest;
	c_244c10 *callback;
	s_244980_output *output;
	shape_3009e0 const *shape;

	result_2df6e0 function_301720(void const *shape, void const *tree, void const *ray, void *output);
	void function_301800(void const *shape, void const *tree, s_244980_ray const *ray, s_244980_output *output, c_244c10 *callback);
	void function_3009e0(pending_301800 *pending, void const *root, fixed_ray_301800 const *ray);
};

// a big-endian number of two, three or four bytes
#define READ_2_3009E0(p) (((p)[0] << 8) + (p)[1])
#define READ_3_3009E0(p) (((((p)[0] << 8) + (p)[1]) << 8) + (p)[2])
#define READ_4_3009E0(p) (((((((p)[0] << 8) + (p)[1]) << 8) + (p)[2]) << 8) + (p)[3])

// the position as a copy that may be changed: the caller's at first
__forceinline pending_301800 *writable_3009e0(pending_301800 *&position, pending_301800 &copy)
{
	if (position != &copy)
	{
		copy = *position;
		position = &copy;
	}
	return &copy;
}

// a vector of four copies of a float
__forceinline __m128 splat_3009e0(float value)
{
	__m128 const single = _mm_load_ss(&value);
	return _mm_shuffle_ps(single, single, 0);
}

// the point a fraction of the way from one point to another
__forceinline __m128 lerp_3009e0(__m128 from, __m128 to, float fraction)
{
	__m128 const t = splat_3009e0(fraction);
	return _mm_add_ps(_mm_mul_ps(_mm_sub_ps(*(__m128 const *)g_412420, t), from), _mm_mul_ps(t, to));
}

// score 1022 (was 1037): the same cases, split and bound code as retail, in the
// same order, but the registers differ: retail keeps the commands in esi, the
// position in ebx and the segment in edi with the split's axis on the stack;
// ours keeps the segment on the stack and the first child's offset in edi,
// which shifts nearly every line.
// The ray's walk down the tree: splits test the ray's two ends against the
// two children's ranges along an axis or a diagonal, visiting the near child
// first (recursively, with the ray cut at the split) and then the far one
// with what is left of the ray; bounds cut the ray to a node's range; each
// leaf reached is cast against.
// @retail 0x3009e0
void class_2df670::function_3009e0(pending_301800 *pending, void const *root, fixed_ray_301800 const *segment)
{
	unsigned char const *commands = (unsigned char const *)root;
	pending_301800 *position = pending;
	pending_301800 copy;
	fixed_ray_301800 other;
	long first_offset;
	long second_offset;
	long axis;
	long key;
	long value;
	float first_end;
	float second_start;
	float a;
	float b;
	float low;
	float high;
	for (;;)
	{
		long const op = *commands;
		axis = 999;
		switch (op)
		{
		case 0x13:
			first_end = (float)(commands[1] * 2);
			second_start = (float)(commands[2] * 2);
			a = segment->from.m128_f32[2] + segment->from.m128_f32[1];
			b = segment->to.m128_f32[2] + segment->to.m128_f32[1];
			goto split_4;
		case 0x14:
			first_end = (float)(commands[1] * 2 - 0xff);
			second_start = (float)(commands[2] * 2 - 0xff);
			a = segment->from.m128_f32[1] - segment->from.m128_f32[2];
			b = segment->to.m128_f32[1] - segment->to.m128_f32[2];
			goto split_4;
		case 0x15:
			first_end = (float)(commands[1] * 2);
			second_start = (float)(commands[2] * 2);
			a = segment->from.m128_f32[2] + segment->from.m128_f32[0];
			b = segment->to.m128_f32[2] + segment->to.m128_f32[0];
			goto split_4;
		case 0x16:
			first_end = (float)(commands[1] * 2 - 0xff);
			second_start = (float)(commands[2] * 2 - 0xff);
			a = segment->from.m128_f32[0] - segment->from.m128_f32[2];
			b = segment->to.m128_f32[0] - segment->to.m128_f32[2];
			goto split_4;
		case 0x17:
			first_end = (float)(commands[1] * 2);
			second_start = (float)(commands[2] * 2);
			a = segment->from.m128_f32[1] + segment->from.m128_f32[0];
			b = segment->to.m128_f32[1] + segment->to.m128_f32[0];
			goto split_4;
		case 0x18:
			first_end = (float)(commands[1] * 2 - 0xff);
			second_start = (float)(commands[2] * 2 - 0xff);
			a = segment->from.m128_f32[0] - segment->from.m128_f32[1];
			b = segment->to.m128_f32[0] - segment->to.m128_f32[1];
			goto split_4;
		case 0x19:
			first_end = (float)(commands[1] * 3);
			second_start = (float)(commands[2] * 3);
			a = segment->from.m128_f32[2] + segment->from.m128_f32[1] + segment->from.m128_f32[0];
			b = segment->to.m128_f32[2] + segment->to.m128_f32[1] + segment->to.m128_f32[0];
			goto split_4;
		case 0x1a:
			first_end = (float)((commands[1] - 0x55) * 3);
			second_start = (float)((commands[2] - 0x55) * 3);
			a = segment->from.m128_f32[1] + segment->from.m128_f32[0] - segment->from.m128_f32[2];
			b = segment->to.m128_f32[1] + segment->to.m128_f32[0] - segment->to.m128_f32[2];
			goto split_4;
		case 0x1b:
			first_end = (float)((commands[1] - 0x55) * 3);
			second_start = (float)((commands[2] - 0x55) * 3);
			a = segment->from.m128_f32[0] - segment->from.m128_f32[1] + segment->from.m128_f32[2];
			b = segment->to.m128_f32[0] - segment->to.m128_f32[1] + segment->to.m128_f32[2];
			goto split_4;
		case 0x1c:
			first_end = (float)((commands[1] - 0xaa) * 3);
			second_start = (float)((commands[2] - 0xaa) * 3);
			a = segment->from.m128_f32[0] - segment->from.m128_f32[1] - segment->from.m128_f32[2];
			b = segment->to.m128_f32[0] - segment->to.m128_f32[1] - segment->to.m128_f32[2];
			goto split_4;
		case 0x20:
		case 0x21:
		case 0x22:
			axis = op - 0x20;
			second_start = (float)commands[1];
			second_offset = commands[2];
			commands += 3;
			first_offset = 0;
			first_end = second_start + 1.0f;
			a = segment->from.m128_f32[axis];
			b = segment->to.m128_f32[axis];
			goto split;
		case 0x23:
		case 0x24:
		case 0x25:
			axis = op - 0x23;
			first_end = (float)commands[1];
			second_start = (float)commands[2];
			a = segment->from.m128_f32[axis];
			b = segment->to.m128_f32[axis];
			first_offset = READ_2_3009E0(commands + 3);
			second_offset = READ_2_3009E0(commands + 5);
			commands += 7;
			goto split;
		case 0x10:
		case 0x11:
		case 0x12:
			axis = op - 0x10;
			first_end = (float)commands[1];
			second_start = (float)commands[2];
			a = segment->from.m128_f32[axis];
			b = segment->to.m128_f32[axis];
		split_4:
			second_offset = commands[3];
			commands += 4;
			first_offset = 0;
		split:
			// both ends before the second child: only the first is reached
			if (b < second_start && a < second_start)
			{
				commands += first_offset;
				continue;
			}
			commands += second_offset;
			// both ends past the first child: only the second is reached
			if (a > first_end && b > first_end)
			{
				continue;
			}
			{
				float const high_a = a - first_end;
				__m128 const from = segment->from;
				__m128 const to = segment->to;
				other.from = from;
				other.to = to;
				float const low_a = a - second_start;
				float const high_b = b - first_end;
				float const low_b = b - second_start;
				if (high_a < high_b)
				{
					// the first child first, with the ray cut where it leaves it
					if (high_b * high_a < 0.0f)
					{
						other.to = lerp_3009e0(from, to, high_a / (high_a - high_b));
					}
					function_3009e0(position, commands - second_offset + first_offset, &other);
					if (low_b * low_a < 0.0f)
					{
						((fixed_ray_301800 *)segment)->from = lerp_3009e0(segment->from, segment->to, low_a / (low_a - low_b));
					}
					if (fraction < 1.0f)
					{
						((fixed_ray_301800 *)segment)->to = _mm_sub_ps(lerp_3009e0(this->ray.from, this->ray.to, fraction), tree->origin);
						((fixed_ray_301800 *)segment)->to = _mm_mul_ps(splat_3009e0(position->scale), segment->to);
						((fixed_ray_301800 *)segment)->to = _mm_sub_ps(segment->to, position->offset);
						if (axis < 3 && segment->to.m128_f32[axis] < second_start)
						{
							return;
						}
					}
				}
				else
				{
					// the second child first, with the ray cut where it leaves it
					if (low_b * low_a < 0.0f)
					{
						other.to = lerp_3009e0(from, to, low_a / (low_a - low_b));
					}
					function_3009e0(position, commands, &other);
					if (high_b * high_a < 0.0f)
					{
						((fixed_ray_301800 *)segment)->from = lerp_3009e0(segment->from, segment->to, high_a / (high_a - high_b));
					}
					if (fraction < 1.0f)
					{
						((fixed_ray_301800 *)segment)->to = _mm_sub_ps(lerp_3009e0(this->ray.from, this->ray.to, fraction), tree->origin);
						((fixed_ray_301800 *)segment)->to = _mm_mul_ps(splat_3009e0(position->scale), segment->to);
						((fixed_ray_301800 *)segment)->to = _mm_sub_ps(segment->to, position->offset);
						if (axis < 3 && segment->to.m128_f32[axis] > first_end)
						{
							return;
						}
					}
					commands += first_offset - second_offset;
				}
			}
			continue;
		case 0x29:
		case 0x2a:
		case 0x2b:
			axis = op - 0x29;
			low = (float)READ_3_3009E0(commands + 1) * inverse_scale * position->scale - position->offset.m128_f32[axis];
			high = (float)READ_3_3009E0(commands + 4) * inverse_scale * position->scale - position->offset.m128_f32[axis];
			commands += 7;
			goto bounds;
		case 0x26:
		case 0x27:
		case 0x28:
			axis = op - 0x26;
			low = (float)commands[1];
			high = (float)commands[2];
			commands += 3;
		bounds:
			// the ray cut to the node's range along the axis
			{
				float const a_end = segment->from.m128_f32[axis];
				float const b_end = segment->to.m128_f32[axis];
				long flip;
				if (a_end < b_end)
				{
					if (b_end < low)
					{
						return;
					}
					if (a_end > high)
					{
						return;
					}
					flip = 0;
				}
				else
				{
					if (a_end < low)
					{
						return;
					}
					if (b_end > high)
					{
						return;
					}
					flip = 1;
				}
				__m128 const from = segment->from;
				__m128 const to = segment->to;
				float const high_a = a_end - high;
				float const high_b = b_end - high;
				if (high_a * high_b < 0.0f)
				{
					(&((fixed_ray_301800 *)segment)->from)[1 - flip] = lerp_3009e0(from, to, high_a / (high_a - high_b));
				}
				float const low_a = a_end - low;
				float const low_b = b_end - low;
				if (low_a * low_b < 0.0f)
				{
					(&((fixed_ray_301800 *)segment)->from)[flip] = lerp_3009e0(from, to, low_a / (low_a - low_b));
				}
			}
			continue;
		case 0x05:
			commands += commands[1] + 2;
			continue;
		case 0x06:
			commands += READ_2_3009E0(commands + 1) + 3;
			continue;
		case 0x07:
			commands += READ_3_3009E0(commands + 1) + 4;
			continue;
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		{
			__m128 corner;
			corner.m128_f32[0] = (float)commands[1];
			corner.m128_f32[1] = (float)commands[2];
			corner.m128_f32[2] = (float)commands[3];
			corner.m128_f32[3] = 0.0f;
			((fixed_ray_301800 *)segment)->from = _mm_sub_ps(segment->from, corner);
			((fixed_ray_301800 *)segment)->to = _mm_sub_ps(segment->to, corner);
			float const factor = (float)(1 << op);
			((fixed_ray_301800 *)segment)->from = _mm_mul_ps(splat_3009e0(factor), segment->from);
			((fixed_ray_301800 *)segment)->to = _mm_mul_ps(splat_3009e0(factor), segment->to);
			copy.offset = _mm_mul_ps(splat_3009e0(factor), _mm_add_ps(position->offset, corner));
			copy.depth = position->depth + op;
			copy.scale = factor * position->scale;
			copy.values[0] = position->values[0];
			copy.key_base = position->key_base;
			position = &copy;
			commands += 4;
			continue;
		}
		case 0x09:
		{
			long const delta = commands[1];
			writable_3009e0(position, copy)->key_base += delta;
			commands += 2;
			continue;
		}
		case 0x0a:
		{
			long const delta = READ_2_3009E0(commands + 1);
			writable_3009e0(position, copy)->key_base += delta;
			commands += 3;
			continue;
		}
		case 0x0b:
		{
			long const start = READ_4_3009E0(commands + 1);
			writable_3009e0(position, copy)->key_base = start;
			commands += 5;
			continue;
		}
		// the value in the first of four slots (retail writes the slot the
		// command names, past the end for the other three)
		case 0x60:
		case 0x61:
		case 0x62:
		case 0x63:
			copy.values[op - 0x60] = commands[1];
			commands += 2;
			goto record_value;
		case 0x64:
		case 0x65:
		case 0x66:
		case 0x67:
			copy.values[op - 0x64] = READ_2_3009E0(commands + 1);
			commands += 3;
			goto record_value;
		case 0x68:
		case 0x69:
		case 0x6a:
		case 0x6b:
			copy.values[op - 0x68] = READ_4_3009E0(commands + 1);
			commands += 5;
		record_value:
			value = copy.values[0];
			writable_3009e0(position, copy)->values[0] = value;
			continue;
		case 0x50:
			key = commands[1];
			goto reached;
		case 0x51:
			key = READ_2_3009E0(commands + 1);
			goto reached;
		case 0x52:
			key = READ_3_3009E0(commands + 1);
			goto reached;
		case 0x53:
			key = (READ_2_3009E0(commands + 1) << 16) + READ_2_3009E0(commands + 3);
			goto reached;
		case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
		case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
		case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
		case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
			key = op - 0x30;
			goto reached;
		default:
			g_48017c->slot_1()->function_2d9000("unknown command %i\n", op);
			((class_2d9060 *)g_48017c->slot_1())->function_2d9060();
			*(long *)0 = 0;
			return;
		case 0x00:
			return;
		}
	}

reached:
	key += position->key_base;
	if (ray.filter != 0 && !ray.filter->slot_0(&ray, shape, key).value)
	{
		return;
	}
	char buffer[0x100];
	leaf_3009e0 *leaf = ((shape_3009e0 *)shape)->leaf_at_key(key, buffer);
	if (closest != 0)
	{
		if (!leaf->cast_closest(&ray, closest).value)
		{
			return;
		}
		hit = true;
		field_54 = closest->fraction;
		closest->key = key;
		return;
	}
	hit_info_3009e0 info;
	info.output = output;
	info.field_8 = ((long *)output)[2];
	info.leaf = leaf;
	info.key = key;
	leaf->cast_reporting(&ray, &info, callback);
	field_54 = ((callback_301800 const *)callback)->field_4;
}

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
	shape = (shape_3009e0 const *)shape_;
	tree_301800 const *source = (tree_301800 const *)tree_;
	tree = source;
	closest = (closest_3009e0 *)output_;
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
	ray.filter = input->filter;
	hit = false;
	pending.key_base = 0;
	pending.depth = 0;
	pending.values[0] = 0;
	function_3009e0(&pending, source->root, &fixed);
	result_2df6e0 result;
	result.hit = hit;
	return result;
}

// @retail 0x301800
void class_2df670::function_301800(void const *shape_, void const *tree_, s_244980_ray const *ray_, s_244980_output *output_, c_244c10 *callback_)
{
	shape = (shape_3009e0 const *)shape_;
	output = output_;
	callback = callback_;
	closest = 0;
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
	ray.filter = input->filter;
	hit = false;
	pending.key_base = 0;
	pending.depth = 0;
	pending.values[0] = 0;
	function_3009e0(&pending, source->root, &fixed);
}
