// @flags /O2 /GL-
// Havok (third-party physics library): telling every listed object, then
// destroying itself through the first virtual slot.

class class_2ebc50_object
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
};

struct s_2ebc50_entry
{
	long field_0;
	class_2ebc50_object *object;
};

class class_2ebc50
{
public:
	virtual void slot0(int flags) = 0;

	long field_4;
	long field_8;
	s_2ebc50_entry *entries;
	int count;

	void function_2ebc50();
};

// @retail 0x2ebc50
void class_2ebc50::function_2ebc50()
{
	for (int i = 0; i < count; i++)
	{
		entries[i].object->slot5();
	}
	slot0(1);
}
