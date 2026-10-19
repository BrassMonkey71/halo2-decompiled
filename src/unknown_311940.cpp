// @flags /O2 /GL- /GX
// Havok (third-party physics library): an object built from its description:
// the part object its kind asks for (kind 7 always gets 0x31a6b0's), given the
// description's matrix, vector and value, and the object activated through
// 0x30bc60 while that part's state is set.
#include <math.h>
#include <xmmintrin.h>
#include "derived_311920.h"
#include "tagged_objects_2e4ff0.h"

// the part objects not decompiled yet, each built from two of the
// description's vectors
class class_31ad80
{
public:
	class_31ad80(void const *first, void const *second);
	OBJECT_NEW_3114B0

	char storage[0x110];
};

class class_31a870
{
public:
	class_31a870(void const *first, void const *second);
	OBJECT_NEW_3114B0

	char storage[0x110];
};

class class_3193c0
{
public:
	class_3193c0(void const *first, void const *second);
	OBJECT_NEW_3114B0

	char storage[0xd0];
};

class class_31a6b0
{
public:
	class_31a6b0(void const *first, void const *second);
	OBJECT_NEW_3114B0

	char storage[0xd0];
};

// an object's part, as the object reaches it
class part_311940
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual void slot_5() {}
	virtual void slot_6() {}
	virtual void slot_7(float value) {}
	virtual void slot_8() {}
	virtual void slot_9() {}
	virtual void slot_10() {}
	virtual void slot_11(void const *matrix) {}
	virtual void slot_12() {}
	virtual void slot_13() {}
	virtual void slot_14() {}
	virtual void slot_15(void const *vector) {}
	virtual void slot_16() {}
	virtual void slot_17() {}
	virtual void slot_18() {}
	virtual void slot_19() {}
	virtual void slot_20(void const *value) {}
	virtual void slot_21(void const *value) {}

	char unknown4[0x14 - 4];
	float field_14;
	float field_18;
};

// a 3x3 matrix, one row to a vector
struct matrix_311940
{
	float rows[3][4];
};

// an object's description
struct s_311340
{
	char unknown0[0x20];
	__m128 field_20;
	__m128 field_30;
	__m128 field_40;
	__m128 field_50;
	matrix_311940 field_60;
	__m128 field_90;
	float field_a0;
	float field_a4;
	float field_a8;
	long field_ac;
	long field_b0;
	char kind;
	char field_b5;
};

// a part object for the given kind; for kind 1, 0x311890's when the matrix's
// diagonal terms are within a tenth of their sum of each other, else 0x31ad80's
// @retail 0x311940
static part_311940 *__cdecl function_311940(int kind, void const *first, void const *second,
	float value, matrix_311940 const *matrix, void const *vector)
{
	// retail keeps the kind on the stack, where the caller pushes it
	int const *kind_reference = &kind;
	part_311940 *part;
	switch (kind)
	{
	case 2:
		part = (part_311940 *)new class_311890(first, second);
		break;
	case 4:
		part = (part_311940 *)new class_31ad80(first, second);
		break;
	case 3:
		part = (part_311940 *)new class_311920(first, second);
		break;
	case 5:
		part = (part_311940 *)new class_31a870(first, second);
		break;
	case 1:
	{
		float const x = matrix->rows[0][0];
		float const y = matrix->rows[1][1];
		float const z = matrix->rows[2][2];
		float const sum = x + y + z;
		float const spread = (float)fabs(x - y) + (float)fabs(y - z) + (float)fabs(x - z);
		if (spread < sum * 0.1f)
		{
			part = (part_311940 *)new class_311890(first, second);
		}
		else
		{
			part = (part_311940 *)new class_31ad80(first, second);
		}
		break;
	}
	case 6:
		part = (part_311940 *)new class_3193c0(first, second);
		break;
	default:
		part = (part_311940 *)new class_31a6b0(first, second);
		break;
	}
	if (kind != 6)
	{
		part->slot_11(matrix);
		part->slot_15(vector);
		part->slot_7(value);
	}
	return part;
}

class hkBool
{
public:
	hkBool() {}

	char m_bool;
};

// the object as 0x30bc40 and 0x30bc60 see it
class hkRigidBody
{
public:
	hkBool body_is_simulating(void) const;
	void activate(void);
};

// the object as 0x311690 sees it
class c_library_311690
{
public:
	void update(long value);
};

// the object as 0x3117b0 sees it
class bounded_shape_3117b0
{
public:
	void function_3117b0();
};

// the object: built on the one 0x30beb0 builds
class c_311ba0 : public class_30bf50
{
public:
	c_311ba0(s_311340 const *description);

	char unknown4[0xc - 4];
	void *shape;
	long unknown10;
	char *field_14;
	char unknown18[0x3c - 0x18];
	part_311940 *part;
	bool kind_7;
	char unknown41[3];
	void *group;
	char unknown48[4];
	long field_4c;
	long field_50;
	char unknown54[0xa0 - 0x54];

	// 0x30bc60 called when 0x30bc40 says false and field_44 is set
	void activate_if_inactive_311ba0()
	{
		if (!((hkRigidBody const *)this)->body_is_simulating().m_bool && group != 0)
		{
			((hkRigidBody *)this)->activate();
		}
	}
};

// @retail 0x311ba0
c_311ba0::c_311ba0(s_311340 const *description) : class_30bf50(description)
{
	bool const is_kind_7 = description->kind == 7;
	if (is_kind_7)
	{
		kind_7 = true;
		part = (part_311940 *)new class_31a6b0(&description->field_20, &description->field_30);
		field_14 = (char *)part + 0x60;
	}
	else
	{
		part = function_311940(description->kind, &description->field_20, &description->field_30,
			description->field_a0, &description->field_60, &description->field_90);
		activate_if_inactive_311ba0();
		part->slot_20(&description->field_40);
		activate_if_inactive_311ba0();
		part->slot_21(&description->field_50);
		part->field_14 = description->field_a4;
		part->field_18 = description->field_a8;
		field_14 = (char *)part + 0x60;
		((c_library_311690 *)this)->update(description->field_b5);
		if (shape != 0)
		{
			((bounded_shape_3117b0 *)this)->function_3117b0();
		}
	}
	field_4c = description->field_ac;
	field_50 = description->field_b0;
}
