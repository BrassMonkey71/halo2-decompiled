// @flags /O2 /GL- /GX
// Havok (third-party physics library): an object holding a value, an array of
// 12-byte elements and two vectors that start at the largest float, and a
// kind derived from it; with their creation functions (which take the value
// as their fourth argument).
#include "bounded_2e9530.h"

// @retail 0x2e9530
bounded_2e9530::~bounded_2e9530()
{
}

// @retail 0x2e95a0 deleting bounded_2e9530

// @retail 0x2e95d0
bounded_2e9530::bounded_2e9530(long value_) : counted_2e9530(value_)
{
	minimum = maximum = _mm_set1_ps(3.402823466e+38f);
}

// @retail 0x2e9620
bounded_2e9530 *__cdecl function_2e9620(long arg_0, long arg_1, long arg_2, long value)
{
	return new bounded_2e9530(value);
}

// @retail 0x2eb4e0
derived_2eb4e0 *__cdecl function_2eb4e0(long arg_0, long arg_1, long arg_2, long value)
{
	return new derived_2eb4e0(value);
}

// @retail 0x2ebae0 destructor derived_2eb4e0
