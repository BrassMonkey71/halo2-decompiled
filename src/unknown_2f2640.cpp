// @flags /O2 /GL- /GX
// Havok (third-party physics library): queries between the two sides of a
// pair passed on to the function that runs them, with the sides changed.
#include "pair_agents_2eab70.h"
#include "side_swap_collectors_2eb1d0.h"

void __cdecl function_2f2130(void const *a, void const *b, void const *input, void *collector);

// the query with the two sides the other way round, its hits passed on as seen from the other side
// @retail 0x2f2640
void __cdecl function_2f2640(void const *a, void const *b, void const *input, void *collector)
{
	flipped_collector_2ed110 flipped(collector);
	function_2f2130(b, a, input, &flipped);
}
