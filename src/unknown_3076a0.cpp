// @flags /O2 /GL-
// Havok (third-party physics library): adding a contact for a pair of
// features to a manifold unless it is listed already, or found too far.
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
