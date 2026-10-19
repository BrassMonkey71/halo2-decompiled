// @flags /O2 /GL- /GX
// Havok (third-party physics library): makes a new list of child objects for
// a pair of shapes given the other way round.
#include "child_list_2edd00.h"

// the list with the two shapes the other way round
class swapped_list_2ee1d0 : public list_2eda30
{
public:
	swapped_list_2ee1d0(typed_2edd00 **other, description_2edd00 const *description, context_2edd00 const *context, long arg_3) :
		list_2eda30(description, other, context, arg_3)
	{
	}
};

// @retail 0x2ee1d0
sized_2edd00 *__cdecl function_2ee1d0(typed_2edd00 **other, description_2edd00 const *description, context_2edd00 const *context, long arg_3)
{
	return new swapped_list_2ee1d0(other, description, context, arg_3);
}
