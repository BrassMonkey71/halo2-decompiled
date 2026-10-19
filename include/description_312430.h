#ifndef DESCRIPTION_312430_H
#define DESCRIPTION_312430_H
// Havok (third-party physics library): an object holding a reference and an
// array of 8-byte elements (the layout of 0x30b3a0's object) copies its
// settings into a description and back (0x312430, 0x3124c0); its derived
// objects add their own fields after the base ones.
#include "growable_array_2d91d0.h"

struct pair_312430
{
	long field_0;
	long field_4;
};

struct pairs_312430
{
	ELEMENTS_2D91D0_MEMBERS(pair_312430)
	pair_312430 &operator[](int index) { return data[index]; }
	pair_312430 const &operator[](int index) const { return data[index]; }
	// stores a copy of `value` after the last element, with room already made
	void append_unchecked(pair_312430 const &value) { pair_312430 &slot = data[size]; slot = value; size++; }
};

struct description_312430
{
	long field_0;
	void *field_4;
	unsigned char field_8;
	pairs_312430 pairs;
};

class class_312430
{
public:
	char unknown0[0xc];
	void *field_c;
	char unknown10[0x24 - 0x10];
	unsigned char field_24;
	long field_28;
	char unknown2c[0x30 - 0x2c];
	pairs_312430 pairs;

	// fills the description from the object
	void function_312430(description_312430 *description) const;
	// sets the object from the description
	void function_3124c0(description_312430 const *description);
};

// the object's motion (0x3115a0 reads it) and something it asks a yes-or-no
// question of
class motion_3115a0;
class query_3115a0;

// an object that adds a byte and a word to the description
struct description_30bd90 : description_312430
{
	unsigned char field_18;
	short field_1a;
};

class class_30bd90 : public class_312430
{
public:
	motion_3115a0 *motion;
	char unknown40[0x48 - 0x40];
	unsigned char field_48;
	char unknown49[0x4c - 0x49];
	long field_4c;
	long field_50;
	query_3115a0 *query;
	char unknown58[0x5c - 0x58];
	short field_5c;

	void function_30bd90(description_30bd90 *description) const;
	void function_30be80(description_30bd90 const *description);
};
#endif
