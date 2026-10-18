// @flags /O2 /GL-
// Havok (third-party physics library): a reference-counted object's
// constructor: it takes a reference to the object it is given, and points
// its list's owner at itself.
#include "reference_counted_2d88a0.h"

struct list_30b340
{
	long field_0;
	void *owner;
	void *data;
	int size;
	unsigned long capacity;

	list_30b340() : field_0(0), owner(0), data(0), size(0), capacity(0x80000000) {}
};

class class_30b340 : public referenced_2d88a0
{
public:
	long field_8;
	referenced_2d88a0 *object;
	long field_10;
	long field_14;
	long field_18;
	long field_1c;
	long field_20;
	long field_24;
	list_30b340 list;

	class_30b340(referenced_2d88a0 *object_, long value);
};

// @retail 0x30b340
// not matched yet: retail stores the vtable and reference count before the
// fields and loads the value later
class_30b340::class_30b340(referenced_2d88a0 *object_, long value)
	: field_8(0), object(object_), field_10(-1), field_14(0), field_18(0), field_1c(0), field_20(0), field_24(value)
{
	list.owner = this;
	if (object_)
	{
		object_->reference_count++;
	}
}
