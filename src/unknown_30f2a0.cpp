// @flags /O2 /GL-
// Havok (third-party physics library): destroying the object of 0x30dc80,
// and giving back its block when flags bit 0 is set.
#include "holder_30dc80.h"

// @retail 0x30f2a0
holder_30dc80 *holder_30dc80::function_30f2a0(unsigned int flags)
{
	this->~holder_30dc80();
	if (flags & 1)
	{
		g_memory_2d88a0->release_block(this, 4, 0x1c);
	}
	return this;
}
