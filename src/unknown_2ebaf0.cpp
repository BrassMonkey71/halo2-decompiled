// @flags /O2 /GL- /GX
// Havok (third-party physics library): a creation function choosing between
// two kinds of bounded object by comparing a value reached through each of
// its first two arguments.
#include "bounded_2e9530.h"

struct info_2ebaf0
{
	char unknown0[0x20];
	long field_20;
};

struct holder_2ebaf0
{
	char unknown0[0x10];
	info_2ebaf0 *info;
};

// the value the creation function compares
static inline long kind_2ebaf0(holder_2ebaf0 const *holder)
{
	return holder->info->field_20 - 0x30;
}

// the kind made when the first argument's value is the smaller
class class_412b08 : public bounded_2e9530
{
public:
	class_412b08(long value_) : bounded_2e9530(value_) {}
};

// the kind made otherwise
class class_412b28 : public bounded_2e9530
{
public:
	class_412b28(long value_) : bounded_2e9530(value_) {}
};

// @retail 0x2ebaf0
bounded_2e9530 *__cdecl function_2ebaf0(holder_2ebaf0 **arg_0, holder_2ebaf0 **arg_1, long arg_2, long value)
{
	long second = kind_2ebaf0(*arg_1);
	long first = kind_2ebaf0(*arg_0);
	if (first < second)
	{
		return new class_412b08(value);
	}
	return new class_412b28(value);
}
