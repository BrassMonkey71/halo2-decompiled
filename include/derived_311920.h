#ifndef DERIVED_311920_H
#define DERIVED_311920_H
// Havok (third-party physics library): an object built on another (0x311890
// builds that), adding only its own table (0x311920).

// the object 0x3114d0 builds, which the first one is built on
class class_3114d0
{
public:
	class_3114d0(void const *a, void const *b);
	virtual ~class_3114d0() {}

	char unknown4[0xc0 - 4];
};

// four words that start cleared
struct quad_311890
{
	long value[4];

	quad_311890()
	{
		value[0] = 0;
		value[1] = 0;
		value[2] = 0;
		value[3] = 0;
	}
};

class class_311890 : public class_3114d0
{
public:
	class_311890(void const *a, void const *b);
	virtual ~class_311890() {}

	quad_311890 field_c0;
	quad_311890 field_d0;
	quad_311890 field_e0;
	quad_311890 field_f0;
};

class class_311920 : public class_311890
{
public:
	class_311920(void const *a, void const *b);
	virtual ~class_311920() {}
};

#endif
