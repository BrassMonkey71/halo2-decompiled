// @flags /O2 /GL-
// Havok (third-party physics library): three objects that each add a word to
// one of their lists.
#include "growable_array_2d91d0.h"

ELEMENTS_2D91D0(words_30bdc0, long);
ELEMENTS_2D91D0(pointers_30be00, void *);

class class_30bdc0
{
public:
	char unknown0[0x88];
	words_30bdc0 words;

	void function_30bdc0(long value);
};

// @retail 0x30bdc0
void class_30bdc0::function_30bdc0(long value)
{
	words.append(value);
}

struct s_1d1540
{
	char unknown0[0x70];
	pointers_30be00 pointers;

	void function_30be00(void *arg_0);
};

// @retail 0x30be00
void s_1d1540::function_30be00(void *arg_0)
{
	pointers.append(arg_0);
}

struct s_47f048_object
{
	char unknown0[0x60];
	words_30bdc0 words;

	void function_30be40(long value);
};

// @retail 0x30be40
void s_47f048_object::function_30be40(long value)
{
	words.append(value);
}
