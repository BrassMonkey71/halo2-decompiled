// @flags /O2 /GL-
// Havok (third-party physics library): setting an object from a
// description: its first value and two vectors, each vector's last word
// taken from the description's second value.
#include <xmmintrin.h>

struct class_2df1f0
{
	char unknown0[8];
	long field_8;

	void function_2df200(long const *value);
};

struct s_2ddd00
{
	long field_0;
	long field_4;
	char field_8[8];
	__m128 field_10;
	__m128 field_20;
};

class class_2ddd00
{
public:
	char field_0[0x10];
	__m128 field_10;
	__m128 field_20;

	void function_2ddd00(s_2ddd00 const *arg_0);
};

// @retail 0x2ddd00
void class_2ddd00::function_2ddd00(s_2ddd00 const *arg_0)
{
	((class_2df1f0 *)this)->function_2df200(&arg_0->field_0);
	field_10 = arg_0->field_10;
	((long *)&field_10)[3] = arg_0->field_4;
	field_20 = arg_0->field_20;
	((long *)&field_20)[3] = arg_0->field_4;
}
