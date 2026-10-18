// @flags /O2 /GL-
// Havok (third-party physics library): calls a game object's method as a
// free function.

struct s_1c3d00
{
	unsigned char field_0[0xc];
	void *field_c;
	long field_10;
	unsigned long field_14;

	void function_1c3d00();
};

// @retail 0x30b6f0
void __cdecl function_30b6f0(s_1c3d00 *object)
{
	object->function_1c3d00();
}
