#ifndef PAIR_AGENTS_2EAB70_H
#define PAIR_AGENTS_2EAB70_H
// Havok (third-party physics library): objects that run a query between two
// sides of a pair (each side a shape, a key, a placement and a parent side)
// through a method, and their methods that run the same query with the two
// sides given the other way round, or with one side replaced by the child
// of the shape that wraps it.
#include <xmmintrin.h>

class class_2eab70
{
public:
	void function_2eab70(void const *a, void const *b, void const *input, void *collector);
	void function_2eb170(void const *a, void const *b, void const *input, void *collector);
	void function_2eb8d0(void const *a, void const *b, void const *input, void *collector);
	void function_2fab30(void const *a, void const *b, void const *input, void *collector);
};

class class_2ea530
{
public:
	void function_2ea530(void const *a, void const *b, void const *input, void *collector, void *second_collector);
	void function_2f9740(void const *a, void const *b, void const *input, void *collector, void *second_collector);
};

class class_2ea830
{
public:
	void function_2ea830(void const *a, void const *b, void const *input, void *collector);
	void function_2fabb0(void const *a, void const *b, void const *input, void *collector);
};

class class_2ecf20
{
public:
	void function_2ecf20(void const *a, void const *b, void const *input, void *collector);
	void function_2ed3a0(void const *a, void const *b, void const *input, void *collector);
};

class class_2f1560
{
public:
	void function_2f1560(void const *a, void const *b, void const *input, void *collector);
	void function_2f17d0(void const *a, void const *b, void const *input, void *collector);
};

class class_2f63d0
{
public:
	void function_2f63d0(void const *a, void const *b, void const *input, void *collector);
	void function_2f7790(void const *a, void const *b, void const *input, void *collector);
};

class class_2f8330
{
public:
	void function_2f8330(void const *a, void const *b, void const *input, void *collector);
	void function_2f8620(void const *a, void const *b, void const *input, void *collector);
};

class class_2f4290
{
public:
	void function_2f4290(void const *a, void const *b, void const *input, void *collector);
};

class class_2ed030
{
public:
	void function_2ed030(void const *a, void const *b, void *collector);
	void function_2ed4c0(void const *a, void const *b, void *collector);
};

// a collector of hits, each a point and a normal, in an array it points to
struct hit_2f88a0
{
	__m128 point;
	__m128 normal;
	char unknown20[0x30 - 0x20];
};

struct hits_2f88a0
{
	hit_2f88a0 *data;
	int size;
};

struct hit_collector_2f88a0
{
	hits_2f88a0 *hits;
};

class class_2f7c40
{
public:
	void function_2f7c40(void const *a, void const *b, void const *input, void *collector);
	void function_2f88a0(void const *a, void const *b, void const *input, hit_collector_2f88a0 *collector);
};

class class_2f90a0
{
public:
	void function_2f90a0(void const *a, void const *b, void const *input, void *collector);
	void function_2f94a0(void const *a, void const *b, void const *input, hit_collector_2f88a0 *collector);
};

class class_2fb150
{
public:
	void function_2fb150(void const *a, void const *b, void const *input, void *collector);
	void function_2fb910(void const *a, void const *b, void const *input, hit_collector_2f88a0 *collector);
};

#endif
