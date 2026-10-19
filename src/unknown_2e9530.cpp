// @flags /O2 /GL- /GX
// Havok (third-party physics library): an object holding a value, an array of
// 12-byte elements and two vectors that start at the largest float, and a
// kind derived from it; with their creation functions (which take the value
// as their fourth argument).
#include "bounded_2e9530.h"
#include "child_refresh_2e9210.h"
#include "agent_table_2e5d50.h"

// @retail 0x2e9530
bounded_2e9530::~bounded_2e9530()
{
}

// @retail 0x2e95a0 deleting bounded_2e9530

// @retail 0x2e95d0
bounded_2e9530::bounded_2e9530(long value_) : counted_2e9530(value_)
{
	minimum = maximum = _mm_set1_ps(3.402823466e+38f);
}

// @retail 0x2e9620
bounded_2e9530 *__cdecl function_2e9620(long arg_0, long arg_1, long arg_2, long value)
{
	return new bounded_2e9530(value);
}

// @retail 0x2e9680
void bounded_2e9530::function_2e9680(description_2e9210 const *description, typed_2e9210 **other, context_2e9210 const *context)
{
	function_2e9210(other, description, context);
}

// @retail 0x2eb4e0
derived_2eb4e0 *__cdecl function_2eb4e0(long arg_0, long arg_1, long arg_2, long value)
{
	return new derived_2eb4e0(value);
}

struct body_2ea940;
class bounded_2e9530;
class derived_2eb4e0;
struct input_2ea940;
derived_2eb4e0 *__cdecl function_2eb4e0(long arg_0, long arg_1, long arg_2, long value);
void __cdecl function_2eb1d0(void const *a, void const *b, void const *input, void *collector);
void __cdecl function_2eb290(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, long value);
void __cdecl function_2eb2f0(void const *a, void const *b, void const *input, void *collector, void *second_collector);
bounded_2e9530 *__cdecl function_2e9620(long arg_0, long arg_1, long arg_2, long value);
void __cdecl function_2ead90(void const *a, void const *b, void const *input, void *collector);
void __cdecl function_2ea940(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, void *collector);
void __cdecl function_2ea640(void const *a, void const *b, void const *input, void *collector, void *second_collector);

// registers handlers for pairs of shape types, each pair both ways round
// where the pair differs
// @retail 0x2eb540
void __cdecl function_2eb540(s_1c3a40 *table)
{
	handlers_2e5d50 handlers;
	handlers.handler[0] = (handler_2e5d50)function_2eb4e0;
	handlers.handler[1] = (handler_2e5d50)function_2eb1d0;
	handlers.handler[2] = (handler_2e5d50)function_2eb290;
	handlers.handler[3] = (handler_2e5d50)function_2eb2f0;
	table->function_2e5d50(&handlers, 3, -1);
	handlers.handler[0] = (handler_2e5d50)function_2e9620;
	handlers.handler[1] = (handler_2e5d50)function_2ead90;
	handlers.handler[2] = (handler_2e5d50)function_2ea940;
	handlers.handler[3] = (handler_2e5d50)function_2ea640;
	table->function_2e5d50(&handlers, -1, 3);
}

// @retail 0x2ebae0 destructor derived_2eb4e0
