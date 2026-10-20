// @flags /O2 /GL-
// Havok (third-party physics library): passing queries on to a collector
// with the child's transform composed into the description's transform.
#include "unknown_182d90.h"

struct shape_2ecc80
{
	char field_0[0xc];
	long child;
	s_extent_transform transform;
};

struct vector_2ecc80
{
	__m128 value;

	void operator=(vector_2ecc80 const &other) { value = other.value; }
};

struct placement_2ecc80
{
	vector_2ecc80 field_0;
	vector_2ecc80 field_10;
	s_extent_transform transform;
};

struct description_2ecc80
{
	shape_2ecc80 const *shape;
	long field_4;
	placement_2ecc80 const *placement;
	description_2ecc80 const *parent;

	description_2ecc80() {}
	description_2ecc80(description_2ecc80 const *parent_, placement_2ecc80 const *placement_, shape_2ecc80 const *outer)
	{
		parent = parent_;
		placement = placement_;
		shape_2ecc80 const *inner = (shape_2ecc80 const *)outer->child;
		field_4 = parent->field_4;
		shape = inner;
	}
};

class collector_2ecc80
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3(description_2ecc80 const *description, long arg_1, long arg_2, long arg_3, long arg_4) = 0;
	virtual void slot4(description_2ecc80 const *description, long arg_1, long arg_2, long arg_3) = 0;
};

class class_2ecc80
{
public:
	char field_0[0xc];
	collector_2ecc80 *collector;

	void function_2ecc80(description_2ecc80 const *description, long arg_1, long arg_2, long arg_3);
	void function_2ecd00(description_2ecc80 const *description, long arg_1, long arg_2, long arg_3, long arg_4);
};

// @retail 0x2ecc80
void class_2ecc80::function_2ecc80(description_2ecc80 const *description, long arg_1, long arg_2, long arg_3)
{
	shape_2ecc80 const *shape = description->shape;
	placement_2ecc80 placement;
	placement.field_0 = description->placement->field_0;
	placement.field_10 = description->placement->field_10;
	placement.transform.compose(&description->placement->transform, &shape->transform);
	description_2ecc80 child;
	child.parent = description;
	child.placement = &placement;
	child.field_4 = description->field_4;
	child.shape = (shape_2ecc80 const *)shape->child;
	collector->slot4(&child, arg_1, arg_2, arg_3);
}

// @retail 0x2ecd00
void class_2ecc80::function_2ecd00(description_2ecc80 const *description, long arg_1, long arg_2, long arg_3, long arg_4)
{
	shape_2ecc80 const *shape = description->shape;
	placement_2ecc80 placement;
	placement.field_0 = description->placement->field_0;
	placement.field_10 = description->placement->field_10;
	placement.transform.compose(&description->placement->transform, &shape->transform);
	description_2ecc80 child;
	child.parent = description;
	child.placement = &placement;
	child.field_4 = description->field_4;
	child.shape = (shape_2ecc80 const *)shape->child;
	collector->slot3(&child, arg_1, arg_2, arg_3, arg_4);
}

class typed_2ecd80
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual long type() { return 0; }
};

typedef void (__cdecl *handler_2ecd80)(description_2ecc80 const *description, typed_2ecd80 **other, void *dispatcher, long arg_3, long arg_4);

struct dispatcher_2ecd80
{
	char field_0[0x318c];
	handler_2ecd80 handlers[1][32];
};

// passing a pair on to the handler a table picks by the two shapes' types
// @retail 0x2ecd80
void __cdecl function_2ecd80(description_2ecc80 const *description, typed_2ecd80 **other, dispatcher_2ecd80 **dispatcher, long arg_3, long arg_4)
{
	shape_2ecc80 const *shape = description->shape;
	placement_2ecc80 placement;
	placement.field_0 = description->placement->field_0;
	placement.field_10 = description->placement->field_10;
	// Retail reads the placement pointer again for composition after copying
	// the two vectors; keep this read separate from those bounds reads.
	placement.transform.compose(&(*(placement_2ecc80 const *const volatile *)&description->placement)->transform, &shape->transform);
	description_2ecc80 child(description, &placement, shape);
	long first = ((typed_2ecd80 *)child.shape)->type();
	long second = (*other)->type();
	(*dispatcher)->handlers[first][second](&child, other, dispatcher, arg_3, arg_4);
}
