// @flags /O2 /GL-
// Havok (third-party physics library): an object passing on one of its
// 16-byte elements, picked by an index the caller points to.

struct element_2e1090
{
	long value[4];
};

class class_2e1090
{
public:
	char unknown0[0x40];
	element_2e1090 *elements;

	void function_2e0020(element_2e1090 const *element);
	void function_2e1090(long const *index);
};

// @retail 0x2e1090
void class_2e1090::function_2e1090(long const *index)
{
	function_2e0020(&elements[*index]);
}
