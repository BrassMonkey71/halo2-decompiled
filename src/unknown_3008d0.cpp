// @flags /O2 /GL-
// Havok (third-party physics library): starting a query of a tree of cells
// for the keys of the cells a sphere touches, the sphere taken into the
// tree's fixed-point grid; and a method that increments the counter at
// offset 0x24.
#include <xmmintrin.h>

struct s_surface_key_array;

// a value rounded to the nearest integer by the FPU
__forceinline int round_3008d0(float value)
{
	int result;
	__asm
	{
		fld value
		fistp result
	}
	return result;
}

// a tree's grid: its origin, its scale, and its nodes
struct tree_3008d0
{
	float origin[3];
	float scale;
	char unknown10[0x30 - 0x10];
	unsigned char nodes[1];
};

// a box of cells around the sphere, in whole cells
struct cell_box_300290
{
	long x;
	long y;
	long z;
	long radius;
	long field_10;
	long field_14;
	long field_18;
	long field_1c;
	long field_20;
	long field_24;
};

class class_3008d0
{
public:
	s_surface_key_array *keys;
	long unknown4[3];
	long x;
	long y;
	long z;
	long radius;

	void function_3008d0(void const *tree, const __m128 *sphere, s_surface_key_array *keys);
	void function_300290(cell_box_300290 const *box, unsigned char const *node);
};

// the sphere's centre and radius in the tree's fixed-point grid, and the
// walk of the tree from its root
// @retail 0x3008d0
void class_3008d0::function_3008d0(void const *tree_, const __m128 *sphere, s_surface_key_array *keys_)
{
	tree_3008d0 const *tree = (tree_3008d0 const *)tree_;
	keys = keys_;
	float const *centre = (float const *)sphere;
	unsigned char const *const nodes = tree->nodes;
	x = round_3008d0((centre[0] - tree->origin[0]) * tree->scale) - 1;
	y = round_3008d0((centre[1] - tree->origin[1]) * tree->scale) - 1;
	z = round_3008d0((centre[2] - tree->origin[2]) * tree->scale) - 1;
	radius = round_3008d0(centre[3] * tree->scale);
	cell_box_300290 box;
	box.x = x >> 16;
	box.radius = (radius >> 16) + 1;
	box.y = y >> 16;
	box.field_10 = 0;
	box.field_14 = 0;
	box.field_18 = 0;
	box.field_1c = 0;
	box.field_24 = 0;
	box.z = z >> 16;
	box.field_20 = 0x10;
	function_300290(&box, nodes);
}

struct class_3009b0
{
    char unknown0[0x24];
    long field_24;

    void function_3009b0();
};

// @retail 0x3009b0
void class_3009b0::function_3009b0()
{
    field_24++;
}
