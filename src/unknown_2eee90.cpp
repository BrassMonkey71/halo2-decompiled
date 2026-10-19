// @flags /O2 /GL-
// Havok (third-party physics library): registering the handlers for pairs of
// shape types in the handler table.
#include "agent_table_2e5d50.h"

void *__cdecl function_2ee390(long arg_0, long arg_1, long arg_2, long value);
void __cdecl function_2ee500(void const *a, void const *b, void const *input, void *collector);
void __cdecl function_2ee8b0(void const *a, void const *b, void const *input, void *collector);
void __cdecl function_2fe830(void const *a, void const *b, void const *input, void *collector, void *second_collector);

// registers handlers for pairs of shape types, each pair both ways round
// where the pair differs
// @retail 0x2eee90
void __cdecl function_2eee90(s_1c3a40 *table)
{
	handlers_2e5d50 handlers;
	handlers.handler[0] = (handler_2e5d50)function_2ee390;
	handlers.handler[1] = (handler_2e5d50)function_2ee500;
	handlers.handler[2] = (handler_2e5d50)function_2ee8b0;
	handlers.handler[3] = (handler_2e5d50)function_2fe830;
	table->function_2e5d50(&handlers, 1, 1);
}
