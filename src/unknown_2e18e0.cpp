// @flags /O2 /GL- /GX
// Havok (third-party physics library): arrays whose storage comes from the
// allocator's stack area, for elements of 2, 16, 4 and 1 bytes: their
// destructors, which return the storage to the stack area. An array
// holds its storage, its size, and its capacity, whose top bit says the array
// does not own the storage. (The array types are stamped out by macro: the
// build compiles template bodies where they cannot be inlined.)
#include "reference_counted_2d88a0.h"
#include <xmmintrin.h>

#define ARRAY_2E1850(name, T) 	struct name 	{ 		T *data; 		long size; 		unsigned long capacity_and_flags; 		name() : data(0), size(0), capacity_and_flags(0x80000000) {} 		~name() 		{ 			if ((capacity_and_flags & 0x80000000) == 0) 			{ 				g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(T), 0x12); 			} 		} 	};

#define STACK_ARRAY_2E1850(name, base, T) 	struct name : base 	{ 		T *stack_block; 		long stack_capacity; 		name(long capacity); 		~name(); 	};

ARRAY_2E1850(array_shorts_2e1850, short)
STACK_ARRAY_2E1850(shorts_2e1850, array_shorts_2e1850, short)

// @retail 0x2e18e0
shorts_2e1850::~shorts_2e1850()
{
	g_memory_2d88a0->release_stack(stack_block, (stack_capacity * sizeof(short) + 15) & ~15);
}

ARRAY_2E1850(array_vectors_2e1980, __m128)
STACK_ARRAY_2E1850(vectors_2e1980, array_vectors_2e1980, __m128)

// @retail 0x2e1a10
vectors_2e1980::~vectors_2e1980()
{
	g_memory_2d88a0->release_stack(stack_block, (stack_capacity * sizeof(__m128) + 15) & ~15);
}

ARRAY_2E1850(array_longs_2e1ab0, long)
STACK_ARRAY_2E1850(longs_2e1ab0, array_longs_2e1ab0, long)

// @retail 0x2e1b40
longs_2e1ab0::~longs_2e1ab0()
{
	g_memory_2d88a0->release_stack(stack_block, (stack_capacity * sizeof(long) + 15) & ~15);
}

ARRAY_2E1850(array_bytes_2e1be0, char)
STACK_ARRAY_2E1850(bytes_2e1be0, array_bytes_2e1be0, char)

// @retail 0x2e1c70
bytes_2e1be0::~bytes_2e1be0()
{
	g_memory_2d88a0->release_stack(stack_block, (stack_capacity * sizeof(char) + 15) & ~15);
}
