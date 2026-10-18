// @flags /O2 /GL- /GX
// Havok (third-party physics library): destroys an object holding a value and
// an array of pointers, releasing the storage unless the array does not own
// it.
#include "reference_counted_2d88a0.h"

struct array_2ede70
{
	void **data;
	long size;
	unsigned long capacity_and_flags;

	~array_2ede70()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(void *), 0x12);
		}
	}
};

class array_owner_2ede70 : public referenced_2d88a0
{
public:
	long value;
	array_2ede70 items;
};

// @retail 0x2ede70 destructor array_owner_2ede70
