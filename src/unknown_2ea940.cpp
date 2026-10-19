// @flags /O2 /GL- /GX
// Havok (third-party physics library): a query of one shape against a shape
// holding a tree of parts: the first shape's bounds, taken into the tree's
// frame, give the keys of the parts they overlap, and every part a filter
// accepts is passed with the first shape to the query function for the two
// kinds. Each phase is marked in the timing stream.
#include "reference_counted_2d88a0.h"
#include "timer_mark_2ebc80.h"
#include <xmmintrin.h>

__forceinline void timer_add_2ea940(char const *label)
{
	timer_mark_2ebc80 *mark = (timer_mark_2ebc80 *)g_480154;
	bool const room = (char *)mark < g_480158;
	if (room)
	{
		mark->label = label;
		unsigned long time;
		__asm
		{
			rdtsc
			mov time, eax
		}
		mark->time = time;
		g_480154 = (char *)(mark + 1);
	}
}

// three axes and a position (0x2da4d0)
struct c_query_transform
{
	__m128 axes[3];
	__m128 position;
	void inverse_product(const c_query_transform *a, const c_query_transform *b);
};

// where a body sits: two vectors, then its transform
struct placement_2ea940
{
	__m128 field_0;
	__m128 field_10;
	c_query_transform transform;
};

// a box given by its two corners
struct bounds_2ea940
{
	__m128 minimum;
	__m128 maximum;
};

// the keys of the parts a query found, held in place for up to 128 of them
struct key_array_2ea940
{
	long *data;
	long size;
	unsigned long capacity_and_flags;
	long storage[128];

	key_array_2ea940() : data(storage), size(0), capacity_and_flags(128 | 0x80000000) {}
	~key_array_2ea940()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(long), 0x12);
		}
	}
};

class shape_2ea940
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	// the shape's kind
	virtual long kind() const { return 0; }
	// the shape's bounds under a transform, widened by a tolerance
	virtual void bounds(c_query_transform const *transform, float tolerance, bounds_2ea940 *out) const {}
	virtual void slot_7() {}
	virtual void slot_8() {}
	virtual void slot_9() {}
	virtual void slot_10() {}
	virtual void slot_11() {}
	// the keys of the parts whose bounds overlap a box
	virtual void overlapping_keys(bounds_2ea940 const *bounds, key_array_2ea940 *keys) const {}
	// a container's part, built in the buffer given when it must be
	virtual shape_2ea940 const *part(long key, char *buffer) const { return 0; }
};

// a shape holding a tree over the parts of a container
class tree_shape_2ea940 : public shape_2ea940
{
public:
	long field_4;
	long field_8;
	shape_2ea940 const *container;
};

// one side of a query: a shape, the key of the part concerned, where it sits,
// and the side it is a part of
struct body_2ea940
{
	shape_2ea940 const *shape;
	long key;
	placement_2ea940 const *placement;
	body_2ea940 const *parent;
};

// the one-byte answer of a filter, returned through a hidden pointer
class answer_2ea940
{
public:
	answer_2ea940() {}

	char value;
};

struct input_2ea940;

// whether one part of a container may meet the other side
class filter_2ea940
{
public:
	virtual answer_2ea940 accepts(input_2ea940 const *input, body_2ea940 const *other, body_2ea940 const *container_body, shape_2ea940 const *container, long key) const = 0;
};

typedef void (__cdecl *pair_query_2ea940)(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, void *collector);

// per-kind flags, then tables of query functions indexed by the kinds of the
// two sides
struct dispatcher_2ea940
{
	char unknown0[0x218c];
	pair_query_2ea940 queries_218c[32][32];
};

// a query's input: the dispatcher, the filter and the tolerance
struct input_2ea940
{
	dispatcher_2ea940 *dispatcher;
	filter_2ea940 *filter;
	float tolerance;
};

// @retail 0x2ea940
void __cdecl function_2ea940(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, void *collector)
{
	timer_add_2ea940("LtBvTree");
	body_2ea940 part;
	c_query_transform a_in_b;
	a_in_b.inverse_product(&b->placement->transform, &a->placement->transform);
	bounds_2ea940 bounds;
	a->shape->bounds(&a_in_b, input->tolerance, &bounds);
	tree_shape_2ea940 const *tree = (tree_shape_2ea940 const *)b->shape;
	key_array_2ea940 keys;
	tree->overlapping_keys(&bounds, &keys);
	timer_add_2ea940("StNarrowPhase");
	long const kind_a = a->shape->kind();
	part.parent = b;
	part.placement = b->placement;
	long const *const end = keys.data + keys.size;
	shape_2ea940 const *container = tree->container;
	__declspec(align(16)) char buffer[0x100];
	for (long const *key = keys.data; key != end; key++)
	{
		if (input->filter->accepts(input, a, b, container, *key).value)
		{
			part.shape = container->part(*key, buffer);
			part.key = *key;
			input->dispatcher->queries_218c[kind_a][part.shape->kind()](a, &part, input, collector);
		}
	}
	timer_add_2ea940("lt");
}
