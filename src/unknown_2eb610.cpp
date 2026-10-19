// @flags /O2 /GL- /GX
// Havok (third-party physics library): a second copy of 0x2eb290's query: the
// two sides swapped for the tree query, into a collector of the nearest
// result.

struct body_2ea940;
struct input_2ea940;

void __cdecl function_2ea940(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, void *collector);

// a collector that starts with no result: the largest float as its distance
class nearest_2eb610
{
public:
	nearest_2eb610() : distance(3.40282347e+38f) {}
	virtual ~nearest_2eb610() {}

	float distance;
};

class nearest_value_2eb610 : public nearest_2eb610
{
public:
	nearest_value_2eb610(long value_) : value(value_) {}

	long value;
};

// @retail 0x2eb610
void __cdecl function_2eb610(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, long value)
{
	nearest_value_2eb610 collector(value);
	function_2ea940(b, a, input, &collector);
}
