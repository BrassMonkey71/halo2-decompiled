// @flags /O2 /GL- /GX
// Havok (third-party physics library): an array of 48-byte elements whose
// storage comes from the allocator's stack area: its constructor and
// destructor (the same shape as the arrays in unknown_2e18e0.cpp).
#include "reference_counted_2d88a0.h"

// a block from the top of the allocator's stack area, or from its slot 9 when
// the area is too small
inline void *stack_allocate_2faeb0(long size)
{
	memory_2d88a0 *memory = g_memory_2d88a0;
	long free = memory->stack_free;
	if (size > free)
	{
		return memory->allocate_stack_overflow(size);
	}
	char *block = memory->stack_cursor;
	memory->stack_cursor = block + size;
	memory->stack_free = free - size;
	return block;
}

struct element_2faeb0
{
	char bytes[0x30];
};

struct array_2faeb0
{
	element_2faeb0 *data;
	long size;
	unsigned long capacity_and_flags;

	array_2faeb0() : data(0), size(0), capacity_and_flags(0x80000000) {}
	~array_2faeb0()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(element_2faeb0), 0x12);
		}
	}
};

struct stack_array_2faeb0 : array_2faeb0
{
	element_2faeb0 *stack_block;
	long stack_capacity;

	stack_array_2faeb0(long capacity);
	~stack_array_2faeb0();
};

// @retail 0x2faeb0
stack_array_2faeb0::stack_array_2faeb0(long capacity)
{
	void *block = stack_allocate_2faeb0((capacity * sizeof(element_2faeb0) + 15) & ~15);
	capacity_and_flags = capacity | 0x80000000;
	stack_capacity = capacity;
	data = (element_2faeb0 *)block;
	stack_block = (element_2faeb0 *)block;
}

// @retail 0x2faf50
stack_array_2faeb0::~stack_array_2faeb0()
{
	g_memory_2d88a0->release_stack(stack_block, (stack_capacity * sizeof(element_2faeb0) + 15) & ~15);
}
