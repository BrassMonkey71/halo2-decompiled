// @flags /O2 /GL- /GX
// Havok (third-party physics library): the constructor of a list of child
// objects for a shape holding children: one object per child, made by the
// handler a table picks by the two shapes' types when the filter accepts the
// child, else the shared empty object.
#include "growable_array_2d91d0.h"

struct object_4805a4;
object_4805a4 *__cdecl function_301a40();

struct key_entry_2edd00
{
	long key;
	long value;
};

class shape_2edd00
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual void slot_5() {}
	virtual void slot_6() {}
	virtual void slot_7() {}
	virtual void slot_8() {}
	virtual void slot_9() {}
	virtual long child_count() const { return 0; }

	long field_4;
	long field_8;
	key_entry_2edd00 *entries;
};

struct description_2edd00
{
	shape_2edd00 const *shape;
	long field_4;
	long field_8;
};

struct child_description_2edd00
{
	long key;
	long index;
	long field_8;
	description_2edd00 const *parent;
};

struct typed_2edd00
{
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual long type() { return 0; }
};

class child_2edd00;
struct context_2edd00;

typedef child_2edd00 *(__cdecl *handler_2edd00)(child_description_2edd00 const *child, typed_2edd00 **other, context_2edd00 const *context, long arg_3);

struct dispatcher_2edd00
{
	char unknown0[0x18c];
	handler_2edd00 handlers[1][32];
};

struct bool_result_2edd00
{
	bool value;
};

class filter_2edd00
{
public:
	virtual bool_result_2edd00 accept(context_2edd00 const *context, typed_2edd00 **other, description_2edd00 const *parent, shape_2edd00 const *shape, long index) = 0;
};

struct context_2edd00
{
	dispatcher_2edd00 *dispatcher;
	filter_2edd00 *filter;
};

// an array that starts out in the room for four children held inside it
struct children_2edd00
{
	ELEMENTS_2D91D0_MEMBERS(child_2edd00 *)
	child_2edd00 *embedded[4];

	children_2edd00()
	{
		data = embedded;
		size = 0;
		capacity_and_flags = 0x80000004;
	}
	~children_2edd00()
	{
		if ((capacity_and_flags & 0x80000000) == 0)
		{
			g_memory_2d88a0->release_block(data, (capacity_and_flags & 0x7fffffff) * sizeof(child_2edd00 *), 0x12);
		}
	}
};

// sized by its allocator, but with no reference count of its own
class sized_2edd00
{
public:
	unsigned short memory_size;
	unsigned short reference_count;
	long field_8;

	sized_2edd00(long field_8_) : field_8(field_8_) {}
	virtual ~sized_2edd00() {}
};

class list_2eda30 : public sized_2edd00
{
public:
	children_2edd00 children;

	list_2eda30(description_2edd00 const *description, typed_2edd00 **other, context_2edd00 const *context, long arg_3);
};

// @retail 0x2edd00
list_2eda30::list_2eda30(description_2edd00 const *description, typed_2edd00 **other, context_2edd00 const *context, long arg_3) :
	sized_2edd00(arg_3)
{
	child_description_2edd00 child;
	child.parent = description;
	child.field_8 = description->field_8;
	shape_2edd00 const *shape = description->shape;
	children.resize(shape->child_count());
	for (long i = 0; i < children.size; i++)
	{
		child.key = shape->entries[i].key;
		child.index = i;
		if (context->filter->accept(context, other, description, shape, i).value)
		{
			dispatcher_2edd00 *table = context->dispatcher;
			long first = ((typed_2edd00 *)child.key)->type();
			long second = (*other)->type();
			handler_2edd00 handler = table->handlers[first][second];
			child_2edd00 **slot = &children.data[i];
			*slot = handler(&child, other, context, arg_3);
		}
		else
		{
			child_2edd00 **slot = &children.data[i];
			*slot = (child_2edd00 *)function_301a40();
		}
	}
}
