// @flags /O2 /GL- /GX
// Havok (third-party physics library): destroys an object holding a value and
// an array of 8-byte elements, releasing the storage unless the array does
// not own it.
#include "reference_counted_2d88a0.h"
#include <xmmintrin.h>

struct array_2ec820
{
	void *data;
	long size;
	unsigned long capacity_and_flags;

	~array_2ec820()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * 8, 0x12);
		}
	}
};

class array_owner_2ec820 : public referenced_2d88a0
{
public:
	REFERENCED_NEW_2D88A0(0x1a)

	long value;
	array_2ec820 items;
};

// @retail 0x2ec820 destructor array_owner_2ec820
// @retail 0x2eca20 deleting array_owner_2ec820

// a kind derived from it that adds nothing
class derived_2ecb70 : public array_owner_2ec820
{
};

// @retail 0x2ecb40 deleting derived_2ecb70
// @retail 0x2ecb70 destructor derived_2ecb70

// the queries of a shape collection (0x2ebc50) run with the two sides given
// the other way round, each through a collector that turns results back

struct body_2ebc80;
struct collector_2ebc80;

static __declspec(align(16)) const unsigned long g_4124a0[4] = {0x80000000, 0x80000000, 0x80000000, 0x80000000};

// the hits a collector gathers: a point, a normal and two more vectors' worth
struct hit_2ec940
{
	__m128 point;
	__m128 normal;
	__m128 extra;
};

struct hit_array_2ec940
{
	hit_2ec940 *data;
	int count;
};

struct hit_list_2ec940
{
	hit_array_2ec940 *hits;
};

struct head_2eca50
{
	long field_0;
	long field_4;
	long field_8;
	long field_c;
};

struct query_2eca50
{
	head_2eca50 head;
	__m128 direction;
	long field_20;
	long field_24;
};

class class_2ebc50
{
public:
	virtual void slot0(int flags) = 0;

	void function_2ebc80(body_2ebc80 const *body, void const *arg_1, void const *arg_2, void *arg_3);
	void function_2ebd60(body_2ebc80 const *body, void const *arg_1, void const *arg_2, void *arg_3);
	void function_2ebf50(body_2ebc80 const *body, void const *arg_1, void const *arg_2, void *arg_3, void *arg_4);
	void function_2ec130(body_2ebc80 const *body, void const *arg_1, void const *arg_2, collector_2ebc80 *collector);

	void function_2ec880(void const *other, body_2ebc80 const *body, void const *input, collector_2ebc80 *collector);
	void function_2ec8e0(void const *other, body_2ebc80 const *body, void const *input, void *collector);
	void function_2ec940(void const *other, body_2ebc80 const *body, void const *input, hit_list_2ec940 *collector);
	void function_2eca50(void const *other, body_2ebc80 const *body, query_2eca50 const *query, void *collector, void *second_collector);
};

// a collector that stops a query early once its flag is set
class stopping_collector_2ec880
{
public:
	stopping_collector_2ec880() : early_out(false) {}
	virtual ~stopping_collector_2ec880() {}

	bool early_out;
};

// passes each pair on to another collector with the two sides swapped back
class swapped_collector_2ec880 : public stopping_collector_2ec880
{
public:
	swapped_collector_2ec880(collector_2ebc80 *target) : target(target) {}
	virtual ~swapped_collector_2ec880() {}
	virtual void add_pair(long first, long second) {}

	collector_2ebc80 *target;
};

// a collector that keeps the nearest result, starting from the largest float
class nearest_collector_2ec8e0
{
public:
	nearest_collector_2ec8e0() : distance(3.40282347e+38f) {}
	virtual ~nearest_collector_2ec8e0() {}

	float distance;
};

// passes each hit on to another collector as seen from the other side
class flipped_hit_collector_2ec8e0 : public nearest_collector_2ec8e0
{
public:
	flipped_hit_collector_2ec8e0(void *target) : target(target) {}
	virtual ~flipped_hit_collector_2ec8e0() {}
	virtual void add_hit(void const *hit) {}

	void *target;
};

// passes each result on to another collector with the query's original
// direction
class flipped_collector_2eca50 : public nearest_collector_2ec8e0
{
public:
	flipped_collector_2eca50(__m128 const &direction, void *target) : direction(direction), target(target) {}
	virtual ~flipped_collector_2eca50() {}

	__m128 direction;
	void *target;
};

// @retail 0x2ec880
void class_2ebc50::function_2ec880(void const *other, body_2ebc80 const *body, void const *input, collector_2ebc80 *collector)
{
	swapped_collector_2ec880 swapped(collector);
	function_2ec130(body, other, input, (collector_2ebc80 *)&swapped);
}

// @retail 0x2ec8e0
void class_2ebc50::function_2ec8e0(void const *other, body_2ebc80 const *body, void const *input, void *collector)
{
	flipped_hit_collector_2ec8e0 flipped(collector);
	function_2ebd60(body, other, input, &flipped);
}

// the hits the query adds get their normals flipped
// @retail 0x2ec940
void class_2ebc50::function_2ec940(void const *other, body_2ebc80 const *body, void const *input, hit_list_2ec940 *collector)
{
	int index = collector->hits->count;
	function_2ebc80(body, other, input, collector);
	for (; index < collector->hits->count; index++)
	{
		__m128 &normal = collector->hits->data[index].normal;
		normal = _mm_xor_ps(normal, *(const __m128 *)g_4124a0);
	}
}

// @retail 0x2eca50
void class_2ebc50::function_2eca50(void const *other, body_2ebc80 const *body, query_2eca50 const *query, void *collector, void *second_collector)
{
	query_2eca50 flipped;
	flipped.head = query->head;
	flipped.field_20 = query->field_20;
	flipped.field_24 = query->field_24;
	flipped.direction = _mm_xor_ps(query->direction, *(const __m128 *)g_4124a0);
	flipped_collector_2eca50 first(query->direction, collector);
	if (second_collector)
	{
		flipped_collector_2eca50 second(query->direction, second_collector);
		function_2ebf50(body, other, &flipped, &first, &second);
	}
	else
	{
		function_2ebf50(body, other, &flipped, &first, 0);
	}
}
