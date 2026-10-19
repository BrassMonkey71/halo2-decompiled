// @flags /O2 /GL- /GX
// Havok (third-party physics library): makes a new object for a pair of
// shapes whose first holds a number of parts (0x2f8ff0).
#include "parts_agent_2f8ff0.h"

// @retail 0x2f93e0
sized_2ed170 *__cdecl function_2f93e0(parts_description_2f8ff0 const *description, typed_2ed170 **other, dispatcher_2ed170 **dispatcher, long arg_3)
{
	return new parts_agent_2f8ff0(description, other, dispatcher, arg_3);
}
