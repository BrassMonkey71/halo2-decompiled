// @flags /O2 /GL-
// Havok (third-party physics library): an open-addressing table of keys
// followed by their values; an empty key slot holds 0.

struct bool_2d9240
{
	bool value;

	bool_2d9240(bool value_)
	{
		value = value_;
	}
};

class class_2d9240
{
public:
	unsigned long *slots;
	long field_4;
	long mask;

	int first() const;
	unsigned long word_at(int index) const;
	void store_word_at(int index, unsigned long value);
	int next(int index) const;
	bool_2d9240 is_valid(int index) const;
};

// @retail 0x2d9240
int class_2d9240::first() const
{
	int index;
	for (index = 0; index <= mask; index++)
	{
		if (slots[index] != 0)
		{
			break;
		}
	}
	return index;
}

// @retail 0x2d9260
unsigned long class_2d9240::word_at(int index) const
{
	return slots[mask + index + 1];
}

// @retail 0x2d9280
void class_2d9240::store_word_at(int index, unsigned long value)
{
	slots[mask + index + 1] = value;
}

// @retail 0x2d92a0
int class_2d9240::next(int index) const
{
	for (index++; index <= mask; index++)
	{
		if (slots[index] != 0)
		{
			break;
		}
	}
	return index;
}

// @retail 0x2d92d0
bool_2d9240 class_2d9240::is_valid(int index) const
{
	return bool_2d9240(index <= mask);
}
