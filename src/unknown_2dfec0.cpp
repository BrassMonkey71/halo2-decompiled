// @flags /O2 /GL-
// Havok (third-party physics library): the first entry of a sorted range
// whose 16-bit key is not below a given key: halving while the range is
// longer than 16 entries, then stepping.

struct entry_2dfec0
{
	unsigned short key;
	unsigned short value;
};

class sorted_2dfec0
{
public:
	entry_2dfec0 *first_not_below(entry_2dfec0 *begin, entry_2dfec0 *end, unsigned short key) const;
};

// @retail 0x2dfec0
entry_2dfec0 *sorted_2dfec0::first_not_below(entry_2dfec0 *begin, entry_2dfec0 *end, unsigned short key) const
{
	while (end - begin > 16)
	{
		entry_2dfec0 *middle = begin + ((end - begin) >> 1);
		if (middle->key < key)
		{
			begin = middle;
		}
		else
		{
			end = middle;
		}
	}
	while (begin->key < key)
	{
		begin++;
	}
	return begin;
}
