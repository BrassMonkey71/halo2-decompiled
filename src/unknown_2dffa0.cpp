// @flags /O2 /GL-
// Havok (third-party physics library): taking two entries out of an array,
// keeping the order of the rest.

class array_2dffa0
{
public:
	long *data;
	int size;

	void remove_two(int first, int second);
};

// @retail 0x2dffa0
// not matched yet: retail loads the size into another register and takes 2
// off with lea
void array_2dffa0::remove_two(int first, int second)
{
	long *p = data + first;
	long *end = data + second - 1;
	for (; p < end; p++)
	{
		p[0] = p[1];
	}
	int remaining = size - 2;
	end = data + remaining;
	size = remaining;
	for (; p < end; p++)
	{
		p[0] = p[2];
	}
}
