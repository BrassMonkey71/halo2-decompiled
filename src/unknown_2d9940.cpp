// @flags /O2 /GL-
// Havok (third-party physics library): reading and skipping bytes in a
// buffered stream, refilling the buffer as often as needed.
#include "growable_array_2d91d0.h"

class class_2d99d0
{
public:
	char unknown0[0xc];
	char *buffer;
	int position;
	int end;

	// refills the buffer; nonzero when nothing more could be read
	int function_2d9850();
	int function_2d9940(void *destination, int count);
	int function_2d99d0(int count);
};

// copies `count` bytes out; returns how many were copied, fewer when the
// stream ran out
// @retail 0x2d9940
int class_2d99d0::function_2d9940(void *destination, int count)
{
	char *out = (char *)destination;
	int left = count;
	int available = end - position;
	while (left > available)
	{
		function_2d8db0(out, buffer + position, available);
		out += available;
		left -= available;
		position += available;
		if (function_2d9850())
		{
			return count - left;
		}
		available = end - position;
	}
	function_2d8db0(out, buffer + position, left);
	position += left;
	return count;
}

// skips `count` bytes; returns how many were skipped, fewer when the stream
// ran out
// @retail 0x2d99d0
int class_2d99d0::function_2d99d0(int count)
{
	int left = count;
	int available = end - position;
	while (left > available)
	{
		left -= available;
		if (function_2d9850())
		{
			return count - left;
		}
		available = end - position;
	}
	position += left;
	return count;
}
