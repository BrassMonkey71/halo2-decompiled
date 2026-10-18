// @flags /O2 /GL- /GX
// Havok (third-party physics library): destroys an object holding a value and
// an array of 8-byte elements, releasing the storage unless the array does
// not own it.
#include "reference_counted_2d88a0.h"

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
	long value;
	array_2ec820 items;
};

// @retail 0x2ec820 destructor array_owner_2ec820
