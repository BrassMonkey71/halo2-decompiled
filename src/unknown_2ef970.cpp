// @flags /O2 /GL-
// Havok (third-party physics library): creation functions for small objects
// holding a value (their fourth argument) and a 16-bit index that starts at
// -1.
#include "reference_counted_2d88a0.h"

class valued_2ef970
{
public:
	valued_2ef970(long value_) : value(value_) {}
	virtual ~valued_2ef970() {}
	unsigned short memory_size;
	unsigned short reference_count;
	long value;
};

class indexed_2ef970 : public valued_2ef970
{
public:
	REFERENCED_NEW_2D88A0(0x1a)

	short index;

	indexed_2ef970(long value_) : valued_2ef970(value_), index(-1) {}
};

// @retail 0x2ef970
indexed_2ef970 *__cdecl function_2ef970(long arg_0, long arg_1, long arg_2, long value)
{
	return new indexed_2ef970(value);
}
