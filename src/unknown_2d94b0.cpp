// @flags /O2 /GL-
// Havok (third-party physics library): giving an open-addressing table's
// keys and values back to the allocator.
#include "physics_allocator.h"

class class_2d94b0
{
public:
	void *slots;
	long field_4;
	long mask;

	void release();
};

// @retail 0x2d94b0
void class_2d94b0::release()
{
	havok_allocator()->release(slots, (mask + 1) * 8, 0x12);
}
