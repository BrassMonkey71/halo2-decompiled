// @flags /O2 /GL-
// Havok (third-party physics library): handing back the ids of a list's
// entries from the last, emptying the list.

class class_3029d0_owner
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void release_id(unsigned short id) = 0;
};

struct s_3029d0_entry
{
	char unknown0[0x1c];
	unsigned short id;
	char unknown1e[0x12];
};

// @retail 0x3029d0
void __cdecl function_3029d0(s_3029d0_entry *entries, int *count, class_3029d0_owner *owner)
{
	while (*count != 0)
	{
		--*count;
		owner->release_id(entries[*count].id);
	}
}
