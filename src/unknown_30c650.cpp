// @flags /O2 /GL-
// Havok (third-party physics library): inserting another array's pointers
// into an array of pointers at an index.
#include "growable_array_2d91d0.h"

struct pointers_30c650
{
	ELEMENTS_2D91D0_MEMBERS(void *)

	void function_30c650(long index, pointers_30c650 const *other);
};

// @retail 0x30c650
void pointers_30c650::function_30c650(long index, pointers_30c650 const *other)
{
	long count = other->size;
	long new_size = size + count;
	long tail = size - index;
	ensure_capacity(new_size);
	void **from = data + index;
	void **to = data + (count + index);
	long i;
	for (i = tail - 1; i >= 0; i--)
	{
		to[i] = from[i];
	}
	void *const *source = other->data;
	void **destination = data + index;
	for (i = count - 1; i >= 0; i--)
	{
		destination[i] = source[i];
	}
	size = new_size;
}
