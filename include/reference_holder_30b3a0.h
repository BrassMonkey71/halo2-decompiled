#ifndef REFERENCE_HOLDER_30B3A0_H
#define REFERENCE_HOLDER_30B3A0_H
// Havok (third-party physics library): an object holding a reference to
// another and an array of 8-byte elements (destructor 0x30b3a0, deleting
// destructor 0x30b590).
#include "unknown_0a9f20.h"
#include "reference_counted_2d88a0.h"

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

#endif
