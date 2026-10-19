// @flags /O2 /GL-
// Havok (third-party physics library): a world flushes its list of entities
// waiting to be removed: each one still in an island is removed, and the list
// drops its reference to each.
#include "growable_array_2d91d0.h"

class hkBool
{
public:
	hkBool() {}

	char m_bool;
};

bool __cdecl function_279740(long value);

class deletable_30fc30
{
public:
	virtual void destroy(unsigned int flags) = 0;
};

class hkEntity
{
public:
	unsigned short unknown0[3];
	unsigned short reference_count;
	char unknown8[0x44 - 8];
	void *island;
};

ELEMENTS_2D91D0(entities_30fc30, hkEntity *);

class hkWorld
{
public:
	char unknown0[0xf0];
	entities_30fc30 pending_removals;

	hkBool entity_world_remove(hkEntity *entity);
	void function_30fc30();
};

// @retail 0x30fc30
void hkWorld::function_30fc30()
{
	for (long i = 0; i < pending_removals.size; i++)
	{
		hkEntity *entity = pending_removals.data[i];
		if (entity->island != 0)
		{
			entity_world_remove(entity);
		}
		entity = pending_removals.data[i];
		entity->reference_count--;
		if (entity->reference_count == 0)
		{
			if (function_279740((long)entity))
			{
				entity->reference_count = 1;
			}
			else
			{
				// the deleting destructor, first in the vtable, without the
				// null test `delete` adds
				((deletable_30fc30 *)entity)->destroy(1);
			}
		}
	}
	pending_removals.size = 0;
}
