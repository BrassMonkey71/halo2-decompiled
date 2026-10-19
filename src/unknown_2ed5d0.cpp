// @flags /O2 /GL- /GX
// Havok (third-party physics library): creating the object kept for a pair
// of shapes given the other way round.
#include "pair_agent_2ed170.h"

// @retail 0x2ed5d0
pair_agent_2ed170 *__cdecl function_2ed5d0(typed_2ed170 **other, description_2ed170 const *description, dispatcher_2ed170 **dispatcher, long arg_3)
{
	return new swapped_pair_agent_2ed170(other, description, dispatcher, arg_3);
}
