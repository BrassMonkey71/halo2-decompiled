// @flags /O2 /GL- /GX
// Havok (third-party physics library): an object that holds a reference to
// another lets go of it when it is destroyed.
#include "unknown_0a9f20.h"
#include "reference_counted_2d88a0.h"

bool __cdecl function_279740(long value);

class deletable_2dbc40
{
public:
	virtual void destroy(unsigned int flags) = 0;
};

class class_2dbc40 : public c_reference_a9f20
{
public:
	char field_8[0x30 - 8];
	referenced_2d88a0 *field_30;

	virtual ~class_2dbc40();
};

// @retail 0x2dbc40
class_2dbc40::~class_2dbc40()
{
	referenced_2d88a0 *object = field_30;
	object->reference_count--;
	if (object->reference_count == 0)
	{
		if (function_279740((long)object))
		{
			object->reference_count = 1;
		}
		else
		{
			// the deleting destructor, first in the vtable, without the null
			// test `delete` adds
			((deletable_2dbc40 *)object)->destroy(1);
		}
	}
}
