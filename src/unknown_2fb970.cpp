// @flags /O2 /GL- /GX
// Havok (third-party physics library): creates a kind of bounded object
// (which takes the value as its fourth argument).
#include "bounded_2e9530.h"

class bounded_2fb970 : public bounded_2e9530
{
public:
	bounded_2fb970(long value_) : bounded_2e9530(value_) {}
};

// @retail 0x2fb970
bounded_2fb970 *__cdecl function_2fb970(long arg_0, long arg_1, long arg_2, long value)
{
	return new bounded_2fb970(value);
}
