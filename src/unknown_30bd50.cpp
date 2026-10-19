// @flags /O2 /GL-
// Havok (third-party physics library): removing a listener from an entity's
// listener array; its entry is cleared (the array squeezes out cleared
// entries later), or the entry before the array when it is not there.
#include "description_312430.h"

class hkEntityListener;

struct listener_array_30bd50
{
	hkEntityListener **data;
	int size;
	int capacity;

	int index_of(hkEntityListener *listener) const
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] == listener)
			{
				return i;
			}
		}
		return -1;
	}
};

struct entity_30bd50
{
	char unknown0[0x60];
	listener_array_30bd50 listeners;
};

// the declaration game code calls (include/unknown_1cec30.h)
class hkEntityApi
{
public:
	void removeEntityListener(hkEntityListener *listener);
};

// @retail 0x30bd50
void hkEntityApi::removeEntityListener(hkEntityListener *listener)
{
	listener_array_30bd50 &listeners = ((entity_30bd50 *)this)->listeners;
	int index = listeners.index_of(listener);
	listeners.data[index] = 0;
}

// fills the description from the object, with the byte and the word it adds
// @retail 0x30bd90
void class_30bd90::function_30bd90(description_30bd90 *description) const
{
	function_312430(description);
	description->field_18 = field_48;
	description->field_1a = field_5c;
}
