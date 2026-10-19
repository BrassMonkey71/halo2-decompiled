// @flags /O2 /GL-
// Havok (third-party physics library): removing an entity from the world, or
// queueing it for removal while the world is locked.
#include "growable_array_2d91d0.h"

class entity_316000;

// whether the entity was removed now, given back by value
struct bool_30f8d0
{
	bool value;

	bool_30f8d0(bool value_)
	{
		value = value_;
	}
};

ELEMENTS_2D91D0(entities_30f8d0, entity_316000 *);

class class_30f030
{
public:
	void function_30f6b0();
};

class class_30d320
{
public:
	void function_30d320();
};

class world_30e2c0
{
public:
	void function_30e2c0(entity_316000 *entity);
};

class class_30e140
{
public:
	char unknown0[0x24];
	int pending_count;
	char unknown28[0xf0 - 0x28];
	entities_30f8d0 removals;
	char unknownfc[0x12c - 0xfc];
	char locked;

	void function_30e140(entity_316000 *entity);
	bool_30f8d0 function_30f8d0(entity_316000 *entity);
};

// @retail 0x30f8d0
bool_30f8d0 class_30e140::function_30f8d0(entity_316000 *entity)
{
	if (locked == 1)
	{
		removals.append(entity);
		((referenced_2d88a0 *)entity)->reference_count++;
		return bool_30f8d0(false);
	}
	if (pending_count > 0)
	{
		((class_30f030 *)this)->function_30f6b0();
	}
	function_30e140(entity);
	((class_30d320 *)entity)->function_30d320();
	((world_30e2c0 *)this)->function_30e2c0(entity);
	return bool_30f8d0(true);
}
