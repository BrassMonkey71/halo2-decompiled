// @flags /O2 /GL-
// Havok (third-party physics library): merges two sorted runs of one axis's
// interval endpoints back into place, telling each object where its
// endpoints now sit.
#include "reference_counted_2d88a0.h"

// an array of longs whose storage comes from the allocator's stack area
// (src/unknown_2e18e0.cpp)
struct array_longs_2e1ab0
{
	long *data;
	long size;
	unsigned long capacity_and_flags;

	array_longs_2e1ab0() : data(0), size(0), capacity_and_flags(0x80000000) {}
	~array_longs_2e1ab0()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(long), 0x12);
		}
	}
};

struct longs_2e1ab0 : array_longs_2e1ab0
{
	long *stack_block;
	long stack_capacity;

	longs_2e1ab0(long capacity);
	~longs_2e1ab0();
};

// one end of an object's interval on an axis: its position, whose low bit
// says whether it is the upper end, and the object's index
struct endpoint_2e2190
{
	unsigned short value;
	unsigned short object;
};

// where each axis's lower and upper endpoint index sits in an object's
// 16-byte record, in bytes
static const long g_endpoint_offsets_461ef0[6] = {8, 10, 0, 4, 2, 6};

// the endpoint at out, recorded in its object as sitting at its index
inline void record_endpoint_2e2190(endpoint_2e2190 const *out, endpoint_2e2190 const *endpoints, char *objects, long axis)
{
	long const index = out - endpoints;
	long const offset = g_endpoint_offsets_461ef0[axis * 2 + (out->value & 1)];
	*(unsigned short *)(objects + out->object * 16 + offset) = (unsigned short)index;
}

class endpoint_list_2e2190
{
public:
	endpoint_2e2190 *endpoints;

	void function_2e2190(char *objects, long first_count, long second_count, long axis);
};

// the first run (after the sentinel at the start) is copied aside, then the
// two runs are merged into the list
// @retail 0x2e2190
void endpoint_list_2e2190::function_2e2190(char *objects, long first_count, long second_count, long axis)
{
	longs_2e1ab0 first_copy(first_count);
	first_copy.size = first_count;
	for (long index = 0; index < first_count; index++)
	{
		first_copy.data[index] = ((long *)endpoints)[index];
	}
	endpoint_2e2190 const *first = (endpoint_2e2190 const *)first_copy.data + 1;
	endpoint_2e2190 const *second = endpoints + first_count;
	endpoint_2e2190 *out = endpoints + 1;
	endpoint_2e2190 const *first_end = (endpoint_2e2190 const *)first_copy.data + first_count;
	endpoint_2e2190 const *second_end = endpoints + first_count + second_count;
	while (first->value < second->value)
	{
		first++;
		out++;
	}
	while (first < first_end)
	{
		if (second >= second_end)
		{
			while (first < first_end)
			{
				*out = *first;
				record_endpoint_2e2190(out, endpoints, objects, axis);
				first++;
				out++;
			}
			break;
		}
		while (first->value < second->value && first < first_end)
		{
			*out = *first;
			record_endpoint_2e2190(out, endpoints, objects, axis);
			first++;
			out++;
		}
		while (first->value >= second->value && second < second_end)
		{
			*out = *second;
			record_endpoint_2e2190(out, endpoints, objects, axis);
			second++;
			out++;
		}
	}
	while (second < second_end)
	{
		*out = *second;
		record_endpoint_2e2190(out, endpoints, objects, axis);
		second++;
		out++;
	}
}
