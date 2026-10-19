// @flags /O2 /GL- /GX
// Havok (third-party physics library): makes a new object for a pair of
// shapes given the other way round, whose second holds a number of parts.
#include "parts_agent_2f8ff0.h"

// the object with the two shapes the other way round
class swapped_parts_agent_2f9660 : public parts_agent_2f8ff0
{
public:
	swapped_parts_agent_2f9660(typed_2ed170 **other, parts_description_2f8ff0 const *description, dispatcher_2ed170 **dispatcher, long arg_3) :
		parts_agent_2f8ff0(description, other, dispatcher, arg_3)
	{
	}
};

// @retail 0x2f9660
sized_2ed170 *__cdecl function_2f9660(typed_2ed170 **other, parts_description_2f8ff0 const *description, dispatcher_2ed170 **dispatcher, long arg_3)
{
	return new swapped_parts_agent_2f9660(other, description, dispatcher, arg_3);
}
