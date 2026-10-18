// @flags /O2 /GL-
// Havok (third-party physics library): returns a block to the game's
// allocator (g_480118, slot 5) with its 16-bit size and the pool tag 0x28.
#include "globals.h"

struct block_30c150
{
    long unknown0;
    unsigned short size;
};

// @retail 0x30c150
void __cdecl function_30c150(block_30c150 *block)
{
    g_480118->allocate((long)block, block->size, 0x28);
}
