// @flags /O2 /GL-
// Havok (third-party physics library): destroys an object built on the
// reference object and two interfaces, and frees it when asked.
#include "reference_counted_2d88a0.h"

class class_30d280;

void __fastcall function_30d280(class_30d280 *object);

class deleting_30d250
{
public:
	unsigned long vtable;
	unsigned short memory_size;

	deleting_30d250 *function_30d250(unsigned int flags);
};

// @retail 0x30d250
deleting_30d250 *deleting_30d250::function_30d250(unsigned int flags)
{
	function_30d280((class_30d280 *)this);
	if (flags & 1)
	{
		g_memory_2d88a0->release_block(this, memory_size, 0x22);
	}
	return this;
}
