// @flags /O2 /GL- /GX
// Havok (third-party physics library): an object holding a reference to
// another and an array of 8-byte elements lets go of both when destroyed.
#include "unknown_0a9f20.h"
#include "reference_counted_2d88a0.h"

bool __cdecl function_279740(long value);

class deletable_30b3a0
{
public:
	virtual void destroy(unsigned int flags) = 0;
};

struct element_30b3a0
{
	long field_0;
	long field_4;
};

struct elements_30b3a0
{
	element_30b3a0 *data;
	long size;
	long capacity_and_flags;

	~elements_30b3a0()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			element_30b3a0 *block = data;
			g_memory_2d88a0->release_block(block, (capacity_and_flags & 0x7fffffff) * sizeof(element_30b3a0), 0x12);
		}
	}
};

class class_30b3a0 : public c_reference_a9f20
{
public:
	long field_8;
	referenced_2d88a0 *field_c;
	char field_10[0x30 - 0x10];
	elements_30b3a0 elements;

	virtual ~class_30b3a0();
};

// @retail 0x30b3a0
class_30b3a0::~class_30b3a0()
{
	referenced_2d88a0 *object = field_c;
	if (object)
	{
		object->reference_count--;
		if (object->reference_count == 0)
		{
			if (function_279740((long)object))
			{
				object->reference_count = 1;
			}
			else
			{
				// the deleting destructor, first in the vtable, without the
				// null test `delete` adds
				((deletable_30b3a0 *)object)->destroy(1);
			}
		}
	}
}
