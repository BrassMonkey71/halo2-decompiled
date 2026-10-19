// @flags /O2 /GL- /GX
// Havok (third-party physics library): creating the object kept for a pair
// of shapes one of which is a triangle, holding the terms that solve for a
// point's weights in the triangle's plane, either way round.
#include <xmmintrin.h>
#include "pair_agent_2ed170.h"

void __cdecl function_308910(__m128 const *corners, float *out);

// a shape whose three corners start at its 16th byte
struct triangle_2f0e70
{
	char field_0[0x10];
	__m128 corners[3];
};

class triangle_terms_2f0e70 : public sized_2ed170
{
public:
	unsigned short field_c;
	float terms[4];

	__forceinline triangle_terms_2f0e70(triangle_2f0e70 const **triangle, long arg_3) :
		sized_2ed170(arg_3)
	{
		field_c = 0xffff;
		function_308910((*triangle)->corners, terms);
	}
};

// the same with the two shapes the other way round
class swapped_triangle_terms_2f0e70 : public triangle_terms_2f0e70
{
public:
	__forceinline swapped_triangle_terms_2f0e70(triangle_2f0e70 const **triangle, long arg_3) :
		triangle_terms_2f0e70(triangle, arg_3)
	{
	}
};

// @retail 0x2f0e70
triangle_terms_2f0e70 *__cdecl function_2f0e70(description_2ed170 const *description, triangle_2f0e70 const **other, dispatcher_2ed170 **dispatcher, long arg_3)
{
	return new triangle_terms_2f0e70(other, arg_3);
}

// @retail 0x2f0ef0
swapped_triangle_terms_2f0e70 *__cdecl function_2f0ef0(triangle_2f0e70 const **description, typed_2ed170 **other, dispatcher_2ed170 **dispatcher, long arg_3)
{
	return new swapped_triangle_terms_2f0e70(description, arg_3);
}
