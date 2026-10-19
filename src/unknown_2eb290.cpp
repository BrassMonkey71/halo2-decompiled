// @flags /O2 /GL- /GX
// Havok (third-party physics library): a query of a shape holding a tree of
// parts against another shape, the two sides swapped for the tree query,
// into a collector of the nearest result.

struct body_2ea940;
struct input_2ea940;

void __cdecl function_2ea940(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, void *collector);

// a collector that starts with no result: the largest float as its distance
class nearest_2eb290
{
public:
	nearest_2eb290() : distance(3.40282347e+38f) {}
	virtual ~nearest_2eb290() {}

	float distance;
};

class nearest_value_2eb290 : public nearest_2eb290
{
public:
	nearest_value_2eb290(long value_) : value(value_) {}

	long value;
};

// @retail 0x2eb290
void __cdecl function_2eb290(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, long value)
{
	nearest_value_2eb290 collector(value);
	function_2ea940(b, a, input, &collector);
}
