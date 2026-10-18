// @flags /O2 /GL-
// Havok (third-party physics library): a list of child objects that passes a
// query on to each child, with a description of the child (its key from the
// parent's table, its index, and the parent's description).

struct key_entry_2eda30
{
	long key;
	long value;
};

struct shape_2eda30
{
	char unknown0[0xc];
	key_entry_2eda30 *entries;
};

struct description_2eda30
{
	shape_2eda30 *shape;
	long field_4;
	long field_8;
};

struct child_description_2eda30
{
	long key;
	long index;
	long field_8;
	description_2eda30 const *parent;
};

struct collector_2edb60
{
	long field_0;
	bool done;
};

class child_2eda30
{
public:
	virtual void slot_0() {}
	virtual void query_1(child_description_2eda30 const *child, long arg_1, long arg_2, collector_2edb60 *collector) {}
	virtual void query_2(child_description_2eda30 const *child, long arg_1, long arg_2, long arg_3) {}
	virtual void query_3(child_description_2eda30 const *child, long arg_1, long arg_2, long arg_3, long arg_4) {}
	virtual void query_4(child_description_2eda30 const *child, long arg_1, long arg_2, long arg_3) {}
};

class list_2eda30
{
public:
	char unknown0[0xc];
	child_2eda30 **children;
	long count;

	void function_2eda30(description_2eda30 const *description, long arg_1, long arg_2, long arg_3);
	void function_2eda90(description_2eda30 const *description, long arg_1, long arg_2, long arg_3);
	void function_2edaf0(description_2eda30 const *description, long arg_1, long arg_2, long arg_3, long arg_4);
	void function_2edb60(description_2eda30 const *description, long arg_1, long arg_2, collector_2edb60 *collector);
};

// @retail 0x2eda30
void list_2eda30::function_2eda30(description_2eda30 const *description, long arg_1, long arg_2, long arg_3)
{
	child_description_2eda30 child;
	shape_2eda30 const *shape = description->shape;
	child.parent = description;
	child.field_8 = description->field_8;
	long n = count;
	child_2eda30 **list = children;
	for (long i = 0; i < n; i++)
	{
		child.key = shape->entries[i].key;
		child.index = i;
		(*list)->query_4(&child, arg_1, arg_2, arg_3);
		list++;
	}
}

// @retail 0x2eda90
void list_2eda30::function_2eda90(description_2eda30 const *description, long arg_1, long arg_2, long arg_3)
{
	child_description_2eda30 child;
	shape_2eda30 const *shape = description->shape;
	child.parent = description;
	child.field_8 = description->field_8;
	long n = count;
	child_2eda30 **list = children;
	for (long i = 0; i < n; i++)
	{
		child.key = shape->entries[i].key;
		child.index = i;
		(*list)->query_2(&child, arg_1, arg_2, arg_3);
		list++;
	}
}

// @retail 0x2edaf0
void list_2eda30::function_2edaf0(description_2eda30 const *description, long arg_1, long arg_2, long arg_3, long arg_4)
{
	child_description_2eda30 child;
	shape_2eda30 const *shape = description->shape;
	child.parent = description;
	child.field_8 = description->field_8;
	long n = count;
	child_2eda30 **list = children;
	for (long i = 0; i < n; i++)
	{
		child.key = shape->entries[i].key;
		child.index = i;
		(*list)->query_3(&child, arg_1, arg_2, arg_3, arg_4);
		list++;
	}
}

// @retail 0x2edb60
void list_2eda30::function_2edb60(description_2eda30 const *description, long arg_1, long arg_2, collector_2edb60 *collector)
{
	child_description_2eda30 child;
	shape_2eda30 const *shape = description->shape;
	child.parent = description;
	child.field_8 = description->field_8;
	for (long i = 0; i < count; i++)
	{
		child.key = shape->entries[i].key;
		child.index = i;
		children[i]->query_1(&child, arg_1, arg_2, collector);
		if (collector->done)
		{
			break;
		}
	}
}
