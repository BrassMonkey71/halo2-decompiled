// @flags /O2 /GL-
// Havok (third-party physics library): clearing a flag in every entry of one
// array and a word in every entry of another.

struct entry_30a810
{
	char unknown0[0x44];
	bool flag;
	char unknown45[0xb];
};

struct item_30a810
{
	char unknown0[0x10];
	long field_10;
	char unknown14[0xc];
};

class class_30a810
{
public:
	char unknown0[0x1b0];
	entry_30a810 *entries;
	int entry_count;
	char unknown1b8[0x2100 - 0x1b8];
	item_30a810 *items;
	int item_count;

	void clear_marks();
};

// @retail 0x30a810
void class_30a810::clear_marks()
{
	int i;
	for (i = 0; i < entry_count; i++)
	{
		entries[i].flag = false;
	}
	for (i = 0; i < item_count; i++)
	{
		items[i].field_10 = 0;
	}
}
