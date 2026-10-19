#ifndef TAGGED_OBJECTS_2E4FF0_H
#define TAGGED_OBJECTS_2E4FF0_H
// Havok (third-party physics library): objects whose destructors are not
// written yet, each giving its block back to the allocator with its own tag
// when deleted (the size of the block is the word at +4).
#include "reference_counted_2d88a0.h"
class class_2e4ff0
{
public:
	REFERENCED_NEW_2D88A0(0x1c)
	virtual ~class_2e4ff0();
};

class class_30bf50
{
public:
	REFERENCED_NEW_2D88A0(0x28)
	virtual ~class_30bf50();
};

class class_310a70
{
public:
	REFERENCED_NEW_2D88A0(0x2a)
	virtual ~class_310a70();
};

class class_311410
{
public:
	REFERENCED_NEW_2D88A0(0x28)
	virtual ~class_311410();
};

// an object of 0xe0 bytes made from a source (0x2fdcf0 builds it)
class class_2fdcf0
{
public:
	REFERENCED_NEW_2D88A0(0x22)

	char storage[0xe0];

	class_2fdcf0(void const *source);
};

#endif
