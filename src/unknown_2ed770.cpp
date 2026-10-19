// @flags /O2 /GL- /GX
// Havok (third-party physics library): a pair that tells both sides about
// each other, and calls passed on to a listener.

class class_2ed770_side
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11(long a, long b) = 0;
};

class class_2ed770
{
public:
	virtual void slot0(int flags) = 0;

	long field_4;
	long field_8;
	long field_c;
	long field_10;
	class_2ed770_side *side_a;
	class_2ed770_side *side_b;
	long type_a;
	long type_b;

	void function_2ed770();
};

// @retail 0x2ed770
void class_2ed770::function_2ed770()
{
	if (type_a == 0x16)
	{
		side_a->slot11(field_c, field_10);
	}
	if (type_b == 0x16)
	{
		side_b->slot11(field_10, field_c);
	}
	slot0(1);
}

class class_2ed7b0_listener
{
public:
	virtual void slot0() = 0;
	virtual void slot1(long a, long b) = 0;
};

class class_2ed7b0
{
public:
	void function_2ed7b0(long a, long b, long c, class_2ed7b0_listener *listener);
	void function_2ed7f0(long a, long b, long c, long d);
	void function_2ed800(long a, long b, long c, long d, long e);
};

// @retail 0x2ed7b0
void class_2ed7b0::function_2ed7b0(long a, long b, long c, class_2ed7b0_listener *listener)
{
	listener->slot1(a, b);
}

// @retail 0x2ed7d0
void __cdecl function_2ed7d0(long a, long b, long c, class_2ed7b0_listener *listener)
{
	listener->slot1(a, b);
}

// @retail 0x2ed7f0
void class_2ed7b0::function_2ed7f0(long a, long b, long c, long d)
{
}

// @retail 0x2ed800
void class_2ed7b0::function_2ed800(long a, long b, long c, long d, long e)
{
}

// a pair's starting state, as its constructor sets it: the pair object of
// 0x2ed770 seen from its own class, whose first virtual is its destructor
class shape_2ed810
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual long shape_kind() const { return 0; }
};

struct collidable_2ed810
{
	shape_2ed810 *shape;
	long field_4;
	long field_8;
	collidable_2ed810 *parent;
};

class base_2ed810
{
public:
	base_2ed810(long value) : field_8(value) {}
	virtual ~base_2ed810() {}

	long field_4;
	long field_8;
};

class pair_2ed810 : public base_2ed810
{
public:
	collidable_2ed810 const *root_a;
	collidable_2ed810 const *root_b;
	void *side_a;
	void *side_b;
	long type_a;
	long type_b;

	pair_2ed810(collidable_2ed810 const *a, collidable_2ed810 const *b, long value);
};

// the outermost collidable a collidable hangs from
inline collidable_2ed810 const *root_2ed810(collidable_2ed810 const *collidable)
{
	while (collidable->parent)
	{
		collidable = collidable->parent;
	}
	return collidable;
}

// @retail 0x2ed810
pair_2ed810::pair_2ed810(collidable_2ed810 const *a, collidable_2ed810 const *b, long value)
	: base_2ed810(value)
{
	root_a = root_2ed810(a);
	root_b = root_2ed810(b);
	type_a = a->shape->shape_kind();
	type_b = b->shape->shape_kind();
}
