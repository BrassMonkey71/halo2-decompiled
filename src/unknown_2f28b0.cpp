// @flags /O2 /GL- /GX
// Havok (third-party physics library): creating an object holding a value
// and three 16-bit indices that start unset (0xffff).
#include "bounded_2e9530.h"

class indexed_2f28b0 : public counted_2e9530
{
public:
	REFERENCED_NEW_2D88A0(0x1a)

	unsigned short index_0;
	unsigned short index_1;
	unsigned short index_2;

	indexed_2f28b0(long value_) : counted_2e9530(value_), index_0(0xffff), index_1(0xffff), index_2(0xffff) {}
};

// @retail 0x2f28b0
indexed_2f28b0 *__cdecl function_2f28b0(long arg_0, long arg_1, long arg_2, long value)
{
	return new indexed_2f28b0(value);
}
