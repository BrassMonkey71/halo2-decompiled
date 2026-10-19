// @flags /O2 /GL-
// Havok (third-party physics library): objects that add an entry to one of
// their lists; one of them, while it is not collecting, hands the entry to its
// listeners and to the handler of the entry's owner instead.
#include "growable_array_2d91d0.h"
#include "listener_world_315d20.h"

class hkBool
{
public:
	hkBool() {}

	char m_bool;
};

void __cdecl function_3182b0(listener_world_315d20 *world, void *event);

ELEMENTS_2D91D0(pointers_30ca30, void *);

class handler_30ca30
{
public:
	virtual void slot_0() {}
	virtual void slot_1(void *entry) {}

	char unknown4[0x24 - 4];
	long field_24;
};

struct owner_30ca30
{
	char unknown0[0x44];
	handler_30ca30 *handler;
};

struct entry_30ca30
{
	unsigned short unknown0[3];
	unsigned short reference_count;
	char unknown8[0xc - 8];
	owner_30ca30 *field_c;
	owner_30ca30 *field_10;
};

class c_1d1261
{
public:
	char unknown0[0xfc];
	pointers_30ca30 collected;
	char unknown108[0x12c - 0x108];
	bool holding_entries;

	hkBool function_30ca30(void *arg_0);
};

// @retail 0x30ca30
hkBool c_1d1261::function_30ca30(void *arg_0)
{
	hkBool result;
	entry_30ca30 *entry = (entry_30ca30 *)arg_0;
	if (holding_entries == true)
	{
		collected.append(entry);
		entry->reference_count++;
		result.m_bool = false;
		return result;
	}
	handler_30ca30 *handler = entry->field_c->handler;
	if (handler->field_24 == -1)
	{
		handler = entry->field_10->handler;
	}
	function_3182b0((listener_world_315d20 *)this, entry);
	handler->slot_1(entry);
	result.m_bool = true;
	return result;
}

class c_interface_278b40;

ELEMENTS_2D91D0(interfaces_30cab0, c_interface_278b40 *);

class c_3101c0
{
public:
	char unknown0[0x78];
	interfaces_30cab0 interfaces;

	void function_30cab0(c_interface_278b40 *arg_0);
};

// @retail 0x30cab0
void c_3101c0::function_30cab0(c_interface_278b40 *arg_0)
{
	interfaces.append(arg_0);
}

class class_30caf0
{
public:
	char unknown0[0xb4];
	pointers_30ca30 pointers;

	void function_30caf0(void *pointer);
};

// @retail 0x30caf0
void class_30caf0::function_30caf0(void *pointer)
{
	pointers.append(pointer);
}

class c_2784c4
{
public:
	char unknown0[0x6c];
	pointers_30ca30 pointers;

	void function_30cb30(void *arg_0);
};

// @retail 0x30cb30
void c_2784c4::function_30cb30(void *arg_0)
{
	pointers.append(arg_0);
}
