// @flags /O2 /GL-
// Havok (third-party physics library): a filter over pairs of 32-bit keys.
// Two keys whose top 16 bits are equal and nonzero never pair; otherwise the
// pair is enabled by bit (second & 31) of word (first & 31) of a 32-word
// table. The filter answers through four interfaces: for two keys, and for
// two objects whose keys it reads.

class hkBool
{
public:
	hkBool() {}

	char m_bool;
};

class keyed_2df8f0
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
	virtual void slot_10() {}
	virtual void slot_11() {}
	virtual void slot_12() {}
	virtual void slot_13() {}
	virtual long key(long index) const { return 0; }
};

struct keyed_object_2df9d0
{
	char unknown0[0x1c];
	long key_1c;
	long key_20;
	long key_24;
};

class c_2df9d0
{
public:
	virtual hkBool function_2df9d0(void const *arg_0, void const *arg_1) = 0;
};

class c_contact_rule_filter
{
public:
	virtual void slot_0() {}
};

class c_2df8f0
{
public:
	virtual hkBool function_2df8f0(void const *arg_0, void const *arg_1, long arg_2) = 0;
};

class c_2dfae0
{
public:
	virtual hkBool function_2dfae0(void const *arg_0, void const *arg_1) = 0;
};

class c_contact_rule_fallback
{
public:
	c_contact_rule_fallback()
	{
		reference_count = 1;
	}
	virtual ~c_contact_rule_fallback() {}
	unsigned short memory_size;
	unsigned short reference_count;

	hkBool accepts(long a, long b);
};

class c_2dfbf0 : public c_contact_rule_fallback, public c_2df9d0,
	public c_contact_rule_filter, public c_2df8f0, public c_2dfae0
{
public:
	long field_18;
	unsigned long enabled[32];

	virtual hkBool function_2df9d0(void const *arg_0, void const *arg_1);
	virtual hkBool function_2df8f0(void const *arg_0, void const *arg_1, long arg_2);
	virtual hkBool function_2dfae0(void const *arg_0, void const *arg_1);

	hkBool test(long a, long b) const
	{
		hkBool result;
		if (((a ^ b) & 0xffff0000) == 0 && (a & 0xffff0000) != 0)
		{
			result.m_bool = false;
			return result;
		}
		result.m_bool = (enabled[a & 31] & (1 << (b & 31))) != 0;
		return result;
	}
};

// @retail 0x2df8a0
hkBool c_contact_rule_fallback::accepts(long a, long b)
{
	return static_cast<c_2dfbf0 &>(*this).test(a, b);
}

// @retail 0x2df8f0
hkBool c_2dfbf0::function_2df8f0(void const *arg_0, void const *arg_1, long arg_2)
{
	long b = ((keyed_2df8f0 const *)arg_1)->key(arg_2);
	return test(((keyed_object_2df9d0 const *)arg_0)->key_20, b);
}

// @retail 0x2df9d0
hkBool c_2dfbf0::function_2df9d0(void const *arg_0, void const *arg_1)
{
	return test(((keyed_object_2df9d0 const *)arg_0)->key_1c,
		((keyed_object_2df9d0 const *)arg_1)->key_1c);
}

// @retail 0x2dfae0
hkBool c_2dfbf0::function_2dfae0(void const *arg_0, void const *arg_1)
{
	return test(((keyed_object_2df9d0 const *)arg_0)->key_24,
		((keyed_object_2df9d0 const *)arg_1)->key_1c);
}
