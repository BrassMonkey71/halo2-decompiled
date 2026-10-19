// @flags /O2 /GL-
// Havok (third-party physics library): adding a contact for a pair of
// features to a manifold unless it is listed already, or found too far; and
// adding the contacts of a pair of box edges and their neighbours.
#include <xmmintrin.h>

struct bool_3058b0
{
	bool value;

	bool_3058b0(bool value_)
	{
		value = value_;
	}
};

struct s_3058b0_pair;

class class_3058b0
{
public:
	bool_3058b0 contains(const s_3058b0_pair *pair) const;
};

class table_305f60;

struct key_305f60
{
	unsigned short index;
	unsigned short field_2;
	unsigned short id;
};

// the closest points of two features, their distance, and the features
struct feature_305f60
{
	__m128 first_point;
	__m128 second_point;
	char unknown20[0x34 - 0x20];
	float distance;
	unsigned short kind;
	unsigned short field_3a;
};

class pair_305f60
{
public:
	void function_305f60(table_305f60 *table, feature_305f60 const *feature, key_305f60 *key);
	bool_3058b0 function_306f80(feature_305f60 *feature);
	void function_3076a0(table_305f60 *table, key_305f60 *key, float distance);
	void function_307720(table_305f60 *table, int first_axis, int second_axis, int first_edge, int second_edge,
		__m128 const *first_corner, __m128 const *second_corner, float distance);
};

// @retail 0x3076a0
void pair_305f60::function_3076a0(table_305f60 *table, key_305f60 *key, float distance)
{
	if (((class_3058b0 *)table)->contains((s_3058b0_pair const *)key).value)
	{
		return;
	}
	feature_305f60 feature;
	feature.kind = key->index;
	feature.field_3a = key->field_2;
	if (!function_306f80(&feature).value)
	{
		return;
	}
	if (distance * 0.999f <= feature.distance)
	{
		function_305f60(table, &feature, key);
	}
}

// which of three edges a value names: 0, 1, or 2 for anything else
inline int edge_307720(int value)
{
	if (value == 0)
	{
		return value;
	}
	return value == 1 ? 1 : 2;
}

// the contacts of an edge of each box, named by the corners they start from
// with the edge's axis set, and of the edges beside them
// @retail 0x307720
void pair_305f60::function_307720(table_305f60 *table, int first_axis, int second_axis, int first_edge, int second_edge,
	__m128 const *first_corner, __m128 const *second_corner, float distance)
{
	__m128 first = *first_corner;
	__m128 second = *second_corner;
	first.m128_f32[first_axis] = 1.0f;
	second.m128_f32[second_axis] = 1.0f;
	key_305f60 key;
	key.index = (unsigned short)((((_mm_movemask_ps(first) & 7) + 0x400) << 4) + first_axis);
	key.id = 0;
	key.field_2 = (unsigned short)(((~_mm_movemask_ps(second) & 7) << 4) + second_axis);
	function_3076a0(table, &key, distance);
	unsigned short const first_flip = (unsigned short)(1 << (edge_307720(first_edge) + 4));
	int const second_bit = edge_307720(second_edge);
	key.index ^= first_flip;
	function_3076a0(table, &key, distance);
	key.field_2 ^= (unsigned short)(1 << (second_bit + 4));
	function_3076a0(table, &key, distance);
	key.index ^= first_flip;
	function_3076a0(table, &key, distance);
}
