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
