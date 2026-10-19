// @flags /O2 /GL-
// Havok (third-party physics library): skipping bytes in a buffered stream,
// refilling the buffer as often as needed.

class class_2d99d0
{
public:
	char unknown0[0x10];
	int position;
	int end;

	// refills the buffer; nonzero when nothing more could be read
	int function_2d9850();
	int function_2d99d0(int count);
};

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
