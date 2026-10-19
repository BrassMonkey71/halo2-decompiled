// @flags /O2 /GL- /GX
// Havok (third-party physics library): creating the object kept for a pair of
// convex shapes (constructor 0x2ee2e0).
#include "pair_agent_2ed170.h"

// the object as its constructor's file declares it, with its full size
class convex_pair_2ee2e0 : public sized_2ed170
{
public:
	char unknownc[0xf0 - 0xc];

	convex_pair_2ee2e0(description_2ed170 const *first, description_2ed170 const *second, long arg_3);
};

// @retail 0x2ee390
void *__cdecl function_2ee390(long arg_0, long arg_1, long arg_2, long value)
{
	return new convex_pair_2ee2e0((description_2ed170 const *)arg_0, (description_2ed170 const *)arg_1, value);
}
