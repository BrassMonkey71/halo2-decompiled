// @flags /O2 /GL-
// Havok (third-party physics library): an object holding 16-byte elements,
// each giving a box (0x2e0020): the boxes of all of them into an array, or
// the box of one picked by an index the caller points to.
#include <xmmintrin.h>
#include "growable_array_2d91d0.h"

struct element_2e1090
{
	long value[4];
};

// a box given by its two corners
struct bounds_2e0020
{
	__m128 lower;
	__m128 upper;
};

ELEMENTS_2D91D0_ALIGNED(bounds_array_2e1020, bounds_2e0020);

class class_2e1090
{
public:
	char unknown0[0x40];
	element_2e1090 *elements;
	long element_count;

	void function_2e0020(element_2e1090 const *element, bounds_2e0020 *bounds);
	void function_2e1020(bounds_array_2e1020 *out);
	void function_2e1090(long const *index, bounds_2e0020 *bounds);
};

// the boxes of all the elements, in order
// @retail 0x2e1020
void class_2e1090::function_2e1020(bounds_array_2e1020 *out)
{
	if ((out->capacity_and_flags & 0x7fffffff) < element_count)
	{
		function_2d9160(out, element_count, sizeof(bounds_2e0020));
	}
	out->size = element_count;
	for (int i = 0; i < element_count; i++)
	{
		function_2e0020(&elements[i], &out->data[i]);
	}
}

// @retail 0x2e1090
void class_2e1090::function_2e1090(long const *index, bounds_2e0020 *bounds)
{
	function_2e0020(&elements[*index], bounds);
}
