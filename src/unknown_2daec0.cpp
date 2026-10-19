// @flags /O2 /GL-
// Havok (third-party physics library): whether a dispatcher's table holds
// the creation function at 0x2dae40 for a pair of kinds, or else the one the
// test at 0x2f98a0 looks for.
#include "agent_table_2e5d50.h"

struct result_2f98a0
{
	char value;

	result_2f98a0(bool value_) : value((char)value_) {}
};

typedef void *(__cdecl *create_function_2f98a0)(long arg_0, long arg_1, long arg_2, long value);

void *__cdecl function_2dae40(long arg_0, long arg_1, long arg_2, long value);

struct dispatcher_2f98a0
{
	char unknown0[0x18c];
	create_function_2f98a0 functions[32][32];
};

result_2f98a0 __cdecl function_2f98a0(dispatcher_2f98a0 const *dispatcher, long first, long second);

// the test the pair table uses for whether a pair has a handler; registering
// the handlers below puts the one above in place
typedef result_2f98a0 (__cdecl *pair_test_2daf00)(dispatcher_2f98a0 const *dispatcher, long first, long second);
pair_test_2daf00 g_461f0c = function_2f98a0;

// @retail 0x2daec0
result_2f98a0 __cdecl function_2daec0(dispatcher_2f98a0 const *dispatcher, long first, long second)
{
	if (dispatcher->functions[first][second] == function_2dae40)
	{
		return true;
	}
	return function_2f98a0(dispatcher, first, second);
}

void __cdecl function_2ee500(void const *a, void const *b, void const *input, void *collector);
void __cdecl function_2ee8b0(void const *a, void const *b, void const *input, void *collector);
void __cdecl function_2fe830(void const *a, void const *b, void const *input, void *collector, void *second_collector);

// registers handlers for pairs of shape types, each pair both ways round
// where the pair differs
// @retail 0x2daf00
void __cdecl function_2daf00(s_1c3a40 *table)
{
	handlers_2e5d50 handlers;
	handlers.handler[0] = (handler_2e5d50)function_2dae40;
	handlers.handler[1] = (handler_2e5d50)function_2ee500;
	handlers.handler[2] = (handler_2e5d50)function_2ee8b0;
	handlers.handler[3] = (handler_2e5d50)function_2fe830;
	table->function_2e5d50(&handlers, 23, 1);
	table->function_2e5d50(&handlers, 1, 23);
	table->function_2e5d50(&handlers, 23, 23);
	g_461f0c = function_2daec0;
}
