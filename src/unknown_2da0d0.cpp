// @flags /O2 /GL-
// Havok (third-party physics library): reading the processor time stamp
// counter.

// @retail 0x2da0d0
unsigned __int64 __cdecl function_2da0d0()
{
	unsigned __int64 ticks;
	__asm
	{
		push ebx
		pop ebx
		rdtsc
		mov dword ptr ticks, eax
		mov dword ptr ticks + 4, edx
	}
	return ticks;
}
