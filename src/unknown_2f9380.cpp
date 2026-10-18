// @flags /O2 /GL- /GX
// Havok (third-party physics library): the implicit destructor of a reference-counted
// object holding an array of pointers, which frees the array's storage
// unless the top bit of its capacity says it does not own it.
#include "reference_counted_2d88a0.h"

struct array_2f9380
{
	void **data;
	int size;
	int capacity;

	~array_2f9380()
	{
		if ((capacity & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity & 0x7fffffff) * sizeof(void *), 0x12);
		}
	}
};

class holder_2f9380 : public referenced_2d88a0
{
public:
	REFERENCED_NEW_2D88A0(0x1a)

	long field_8;
	array_2f9380 items;
};

// @retail 0x2f9380 destructor holder_2f9380
// @retail 0x2f9500 deleting holder_2f9380

// a holder that adds nothing to its base
class derived_2f9620 : public holder_2f9380
{
public:
	REFERENCED_NEW_2D88A0(0x1a)
};

// @retail 0x2f9620 deleting derived_2f9620
// @retail 0x2f9650 destructor derived_2f9620
