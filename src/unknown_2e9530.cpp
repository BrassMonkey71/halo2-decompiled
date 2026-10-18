// @flags /O2 /GL- /GX
// Havok (third-party physics library): an object holding a value, an array of
// 12-byte elements and two vectors that start at the largest float, and a
// kind derived from it; with their creation functions (which take the value
// as their fourth argument).
#include "reference_counted_2d88a0.h"
#include <xmmintrin.h>

struct element_2e9530
{
	long value_0;
	long value_4;
	long value_8;
};

struct array_2e9530
{
	element_2e9530 *data;
	long size;
	unsigned long capacity_and_flags;

	array_2e9530() : data(0), size(0), capacity_and_flags(0x80000000) {}
	~array_2e9530()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(element_2e9530), 0x12);
		}
	}
};

class counted_2e9530
{
public:
	counted_2e9530(long value_) : value(value_) {}
	virtual ~counted_2e9530() {}
	unsigned short memory_size;
	unsigned short reference_count;
	long value;
};

class bounded_2e9530 : public counted_2e9530
{
public:
	REFERENCED_NEW_2D88A0(0x1a)

	array_2e9530 elements;
	__m128 minimum;
	__m128 maximum;

	bounded_2e9530(long value_);
	~bounded_2e9530();
};

class derived_2eb4e0 : public bounded_2e9530
{
public:
	derived_2eb4e0(long value_) : bounded_2e9530(value_) {}
};

// @retail 0x2e9530
bounded_2e9530::~bounded_2e9530()
{
}

// @retail 0x2e95d0
bounded_2e9530::bounded_2e9530(long value_) : counted_2e9530(value_)
{
	minimum = maximum = _mm_set1_ps(3.402823466e+38f);
}

// @retail 0x2e9620
bounded_2e9530 *__cdecl function_2e9620(long arg_0, long arg_1, long arg_2, long value)
{
	return new bounded_2e9530(value);
}

// @retail 0x2eb4e0
derived_2eb4e0 *__cdecl function_2eb4e0(long arg_0, long arg_1, long arg_2, long value)
{
	return new derived_2eb4e0(value);
}
