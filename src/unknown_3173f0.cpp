// @flags /O2 /GL- /GX
// Havok (third-party physics library): pairs that begin and end, passed to
// the world's dispatcher while an object collects what it hands back: its
// list of 16-byte entries is copied through as the dispatcher goes, into a
// stack array that then becomes the new list.
#include "stack_array_30d740.h"

// orders each pair by the second words of its two objects, then the pairs
void __cdecl function_372b50(pair_30d870 *pairs, long count);

class pair_listener_315a10
{
public:
	virtual void slot_0() {}
};

// a reference-counted object that is told of the pairs through its second
// base
class pair_listening_315a10 : public referenced_2d88a0, public pair_listener_315a10
{
};

// what the dispatcher hands the pairs to while it runs
struct pair_handler_3173f0
{
	void const *table;
};

class dispatcher_3728c0
{
public:
	char unknown0[0x24];
	pair_handler_3173f0 *handler;
	char unknown28[0x100 - 0x28];
	// the dispatcher's own handler, put back when a caller is done
	pair_handler_3173f0 own_handler;

	void function_3728c0(pair_30d870 const *added, long added_count, pair_30d870 const *removed,
		long removed_count, pair_listener_315a10 *listener);
};

struct tolerance_3173f0;

struct world_3173f0
{
	char unknown0[0xcc];
	tolerance_3173f0 *tolerance;
	pair_listening_315a10 *pair_listener;
	char unknownd4[0x138 - 0xd4];
	dispatcher_3728c0 *dispatcher;
};

// one entry of the object's list
struct entry_3173f0
{
	long field_0;
	long field_4;
	long field_8;
	long field_c;
};

struct entries_3173f0
{
	entry_3173f0 *data;
	long size;
	unsigned long capacity_and_flags;
};

class collector_3173f0
{
public:
	char unknown0[0x1c];
	pair_handler_3173f0 handler;
	world_3173f0 *world;
	char unknown24[0x68 - 0x24];
	entries_3173f0 entries;
	char unknown74[0x98 - 0x74];
	tolerance_3173f0 *tolerance;
	// the entries still to be read, their end, and where the next one kept
	// is written, while the dispatcher runs
	entry_3173f0 *read;
	entry_3173f0 *end;
	entry_3173f0 *write;

	void function_3173f0(pair_30d870 *added, long added_count, pair_30d870 *removed, long removed_count);
};

// @retail 0x3173f0
void collector_3173f0::function_3173f0(pair_30d870 *added, long added_count, pair_30d870 *removed, long removed_count)
{
	if (added_count == 0 && removed_count == 0)
	{
		return;
	}
	function_372b50(added, added_count);
	function_372b50(removed, removed_count);
	vectors_30d9a0 kept(entries.size + added_count);
	read = entries.data;
	end = entries.data + entries.size;
	write = (entry_3173f0 *)kept.data;
	tolerance = world->tolerance;
	world->dispatcher->handler = &handler;
	pair_listener_315a10 *listener = world->pair_listener;
	world->dispatcher->function_3728c0(added, added_count, removed, removed_count, listener);
	world->dispatcher->handler = &world->dispatcher->own_handler;
	while (read < end)
	{
		*write = *read;
		write++;
		read++;
	}
	kept.size = write - (entry_3173f0 *)kept.data;
	if ((long)(entries.capacity_and_flags & 0x7fffffff) < kept.size)
	{
		if ((entries.capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(entries.data, (entries.capacity_and_flags & 0x7fffffff) * sizeof(entry_3173f0), 0x12);
		}
		entries.data = (entry_3173f0 *)g_memory_2d88a0->allocate_block(kept.size * sizeof(entry_3173f0), 0x12);
		entries.capacity_and_flags = kept.size;
	}
	entries.size = kept.size;
	for (long i = 0; i < kept.size; i++)
	{
		entries.data[i] = ((entry_3173f0 *)kept.data)[i];
	}
}
