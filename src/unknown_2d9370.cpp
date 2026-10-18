// @flags /O2 /GL-
// Havok (third-party physics library): finding a key's slot in an
// open-addressing table (mask + 1 when it is absent).

class class_2d9370
{
public:
	unsigned long *slots;
	long field_4;
	unsigned long mask;

	unsigned long find(unsigned long key) const;
};

// @retail 0x2d9370
unsigned long class_2d9370::find(unsigned long key) const
{
	for (unsigned long index = (key >> 4) * 0x9e3779b1 & mask; slots[index] != 0; index = (index + 1) & mask)
	{
		if (slots[index] == key)
		{
			return index;
		}
	}
	return mask + 1;
}
