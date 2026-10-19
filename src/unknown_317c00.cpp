// @flags /O2 /GL- /GX
// Havok (third-party physics library): the narrow phase over a list of
// pairs: every pair with an agent is asked for its contacts into a scratch
// array, and when it finds any they are passed on to the agent's handler;
// bracketed by two marks in the timing stream.
#include "reference_counted_2d88a0.h"
#include "timer_mark_2ebc80.h"

__forceinline void timer_add_317c00(char const *label)
{
	timer_mark_2ebc80 *mark = (timer_mark_2ebc80 *)g_480154;
	bool const room = (char *)mark < g_480158;
	if (room)
	{
		mark->label = label;
		unsigned long time;
		__asm
		{
			rdtsc
			mov time, eax
		}
		mark->time = time;
		g_480154 = (char *)(mark + 1);
	}
}

struct element_317060
{
	char bytes[0x30];
};

// an array of 48-byte elements whose storage comes from the allocator's
// stack area (src/unknown_317060.cpp)
struct array_317060
{
	element_317060 *data;
	long size;
	unsigned long capacity_and_flags;

	array_317060() : data(0), size(0), capacity_and_flags(0x80000000) {}
	~array_317060()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(element_317060), 0x12);
		}
	}
};

struct stack_array_317060 : array_317060
{
	element_317060 *stack_block;
	long stack_capacity;

	stack_array_317060(long capacity);
	~stack_array_317060();
};

// where a pair's contacts are gathered (16-byte aligned)
struct __declspec(align(16)) contacts_317c00
{
	array_317060 *results;
};

struct object_317c00;

class handler_317c00
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	// the contacts found for a pair
	virtual void handle(object_317c00 *a, object_317c00 *b, void const *input, contacts_317c00 *contacts) {}
};

class agent_317c00
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	// the pair's contacts
	virtual void find_contacts(object_317c00 *a, object_317c00 *b, void const *input, contacts_317c00 *contacts) {}

	long field_4;
	handler_317c00 *handler;
};

// a pair: the two objects (each held by its part at +0x10) and their agent
struct pair_317c00
{
	char *a;
	char *b;
	agent_317c00 *agent;
	long field_c;
};

class narrow_phase_317c00
{
public:
	char unknown0[0x68];
	pair_317c00 *pairs;
	long pair_count;

	void function_317c00(void const *input);
};

// @retail 0x317c00
void narrow_phase_317c00::function_317c00(void const *input)
{
	timer_add_317c00("TtNarrowPhase");
	{
		contacts_317c00 contacts;
		stack_array_317060 results(0x40);
		pair_317c00 *pair = pairs;
		int const count = pair_count;
		contacts.results = &results;
		for (int index = count - 1; index >= 0; index--, pair++)
		{
			if (pair->agent != 0)
			{
				contacts.results->size = 0;
				object_317c00 *a = (object_317c00 *)(pair->a - 0x10);
				object_317c00 *b = (object_317c00 *)(pair->b - 0x10);
				pair->agent->find_contacts(a, b, input, &contacts);
				if (contacts.results->size != 0)
				{
					pair->agent->handler->handle(a, b, input, &contacts);
				}
			}
		}
	}
	timer_add_317c00("Et");
}
