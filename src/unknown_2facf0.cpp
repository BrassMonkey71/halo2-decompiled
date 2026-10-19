// @flags /O2 /GL- /GX
// Havok (third-party physics library): a second copy of 0x2f9950's query: a
// shape holding a tree of parts against the child of a wrapping shape, into
// a collector of the nearest result.
#include "child_query_2f9950.h"

// @retail 0x2facf0
void __cdecl function_2facf0(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, long value)
{
	nearest_value_2f9950 collector(value);
	body_2ea940 child(a, a->placement, (wrapper_2f9950 const *)a->shape);
	function_2ea940(b, &child, input, &collector);
}
