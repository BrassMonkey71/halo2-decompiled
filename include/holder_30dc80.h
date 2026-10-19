#ifndef HOLDER_30DC80_H
#define HOLDER_30DC80_H
// Havok (third-party physics library): an object holding a reference-counted
// header and an array of four-byte values.
#include "reference_counted_2d88a0.h"

struct values_30dc80
{
	long *data;
	long size;
	unsigned long capacity_and_flags;

	~values_30dc80()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(long), 0x12);
		}
	}
};

class holder_30dc80
{
public:
	referenced_2d88a0 header;
	values_30dc80 values;

	~holder_30dc80();
	holder_30dc80 *function_30f2a0(unsigned int flags);
};

#endif
