// @flags /O2 /GL-
// Havok (third-party physics library): two queries passed on to the object
// held at +0xc.

struct s_2fc080_result
{
	float values[4];
};

struct s_2fc080_range
{
	long field_0;
	long field_4;
};

struct s_2fc080_input
{
	long field_0;
	s_2fc080_range range;
};

class class_2fc080_target;

struct s_2fc080_query
{
	class_2fc080_target *target;
	s_2fc080_range range;
	const s_2fc080_input *input;
};

class class_2fc080_target
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
	virtual s_2fc080_result slot8(long a, long b) = 0;
	virtual void slot9(long a, const s_2fc080_query *query, long c) = 0;
};

class class_2fc080
{
public:
	char unknown0[0xc];
	class_2fc080_target *target;

	s_2fc080_result function_2fc080(long a, long b);
	void function_2fc0a0(long a, const s_2fc080_input *input, long c);
};

// @retail 0x2fc080
s_2fc080_result class_2fc080::function_2fc080(long a, long b)
{
	return target->slot8(a, b);
}

// @retail 0x2fc0a0
void class_2fc080::function_2fc0a0(long a, const s_2fc080_input *input, long c)
{
	s_2fc080_query query;
	query.target = target;
	query.range = input->range;
	query.input = input;
	query.target->slot9(a, &query, c);
}
