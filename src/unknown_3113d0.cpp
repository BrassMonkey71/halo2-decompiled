// @flags /O2 /GL- /GX
// Havok (third-party physics library): constructs a description in place, in
// the memory it is given.
#include <new>

struct s_311340
{
	s_311340();
};

// @retail 0x3113d0
void __cdecl function_3113d0(void *memory)
{
	new (memory) s_311340;
}
