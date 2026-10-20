// @flags /O2 /GL-
// Havok (third-party physics library): a world flushes its list of entities
// waiting to be removed: each one still in an island is removed, and the list
// drops its reference to each; and the collision part of a world's step.
#include "growable_array_2d91d0.h"
#include "timer_mark_2ebc80.h"

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

// the parts of a world's step run by other classes' code
class c_1d1261
{
public:
	void function_30cda0();
};

class class_30f030
{
public:
	void function_30f6b0();
};

class narrow_phase_317c00
{
public:
	void function_317d30(void const *step, void const *input);
};

struct listener_world_3187a0;
struct listener_world_318830;
void __cdecl function_3187a0(listener_world_3187a0 *world, void *value);
void __cdecl function_3188c0(listener_world_318830 *world, void *first, void *second);

// a step's length and a second term, from the caller
struct s_311100
{
	float delta;
	float field_4;
};

// the terms a step works out from its length (at 0x170 in the world)
struct step_terms_311100
{
	float scaled_delta;
	float scaled_field_4;
	char unknown8[0xc - 8];
	long field_c;
	float field_10;
	char unknown14[0x28 - 0x14];
	float field_28;
	float field_2c;
	float field_30;
	float field_34;

	void scale_by(s_311100 const *description)
	{
		scaled_delta = description->delta * field_10;
		scaled_field_4 = field_c * description->field_4;
		set_products();
	}

	void set_products()
	{
		field_28 = scaled_delta;
		field_2c = scaled_field_4;
		field_30 = field_c * scaled_delta;
		field_34 = field_10 * scaled_field_4;
	}
};
struct step_info_311100
{
	long field_0;
	long field_4;
	long field_8;
	long field_c;
};

// a world seen as the object that runs a step
class c_311100
{
public:
	char unknown0[8];
	narrow_phase_317c00 **islands;
	long island_count;
	char unknown10[0x24 - 0x10];
	long pending_count;
	char unknown28[0xac - 0x28];
	void *island_listener;
	char unknownb0[0xc4 - 0xb0];
	void const *step;
	char unknownc8[0xcc - 0xc8];
	step_info_311100 const *info;
	char unknownd0[0xf4 - 0xd0];
	long pending_removal_count;
	char unknownf8[0x100 - 0xf8];
	long collected_count;
	char unknown104[0x12c - 0x104];
	bool stepping;
	bool collision_pass_running;
	char unknown12e[0x140 - 0x12e];
	step_info_311100 input;
	s_311100 description;
	char unknown158[0x170 - 0x158];
	step_terms_311100 terms;

	void function_30fcb0(s_311100 const *description);
};

// runs the collision part of a world's step: the step's terms set from the
// description, each island's contacts worked out and the island listeners
// told, the pending removals and other work flushed, and the post-collide
// listeners told; marked in the timing stream throughout
// @retail 0x30fcb0
void c_311100::function_30fcb0(s_311100 const *description_)
{
	timer_add_2ebc80("LtSimulate");
	step_info_311100 const *source = info;
	description = *description_;
	input = *source;
	terms.scale_by(description_);
	stepping = true;
	if (pending_count > 0)
	{
		((class_30f030 *)this)->function_30f6b0();
	}
	collision_pass_running = true;
	for (int i = 0; i < island_count; i++)
	{
		islands[i]->function_317d30(step, &input);
		if (island_listener != 0)
		{
			timer_add_2ebc80("TtIslandPostCollideCb");
			collision_pass_running = false;
			function_3188c0((listener_world_318830 *)this, islands[i], (void *)description_);
			collision_pass_running = true;
			timer_add_2ebc80("Et");
		}
	}
	collision_pass_running = false;
	stepping = false;
	if (pending_count > 0)
	{
		((class_30f030 *)this)->function_30f6b0();
	}
	if (pending_removal_count != 0)
	{
		((hkWorld *)this)->function_30fc30();
	}
	if (collected_count != 0)
	{
		((c_1d1261 *)this)->function_30cda0();
	}
	if (pending_count > 0)
	{
		((class_30f030 *)this)->function_30f6b0();
	}
	timer_add_2ebc80("StPostCollideCB");
	function_3187a0((listener_world_3187a0 *)this, (void *)description_);
	timer_add_2ebc80("lt");
}
