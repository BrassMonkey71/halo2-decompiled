// @flags /O2 /GL-
// Havok (third-party physics library): two queries passed on to the object
// held at +0x30.

struct s_2dbe90_result
{
	float values[4];
};

struct s_2dbe90_range
{
	long field_0;
	long field_4;
};

struct s_2dbe90_input
{
	long field_0;
	s_2dbe90_range range;
};

class class_2dbe90_target;

struct s_2dbe90_query
{
	class_2dbe90_target *target;
	s_2dbe90_range range;
	const s_2dbe90_input *input;
};

class class_2dbe90_target
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
	virtual s_2dbe90_result slot8(long a, long b) = 0;
	virtual void slot9(long a, const s_2dbe90_query *query, long c) = 0;
};

class class_2dbe90
{
public:
	char unknown0[0x30];
	class_2dbe90_target *target;

	s_2dbe90_result function_2dbe90(long a, long b);
	void function_2dbeb0(long a, const s_2dbe90_input *input, long c);
};

// @retail 0x2dbe90
s_2dbe90_result class_2dbe90::function_2dbe90(long a, long b)
{
	return target->slot8(a, b);
}

// @retail 0x2dbeb0
// Still differs: retail keeps the member target in edx and copies it into ecx for the
// virtual call, and stores the range's low half after the argument setup; ours reloads
// the member and stores the range low half early.
void class_2dbe90::function_2dbeb0(long a, const s_2dbe90_input *input, long c)
{
	s_2dbe90_query query;
	query.target = target;
	query.range = input->range;
	query.input = input;
	query.target->slot9(a, &query, c);
}
