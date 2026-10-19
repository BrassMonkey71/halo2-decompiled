// @flags /O2 /GL-
// Havok (third-party physics library): constructing a world description in
// a block, when there is one.
#include <new>

struct s_3111d0
{
	s_3111d0();
};

// @retail 0x3112a0
void __cdecl function_3112a0(void *block)
{
	new (block) s_3111d0;
}
