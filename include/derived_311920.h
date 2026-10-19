#ifndef DERIVED_311920_H
#define DERIVED_311920_H
// Havok (third-party physics library): an object built on another (0x311890
// builds that), adding only its own table (0x311920).

class class_311890
{
public:
	class_311890(void const *a, void const *b);
	virtual ~class_311890() {}
};

class class_311920 : public class_311890
{
public:
	class_311920(void const *a, void const *b);
	virtual ~class_311920() {}
};

#endif
