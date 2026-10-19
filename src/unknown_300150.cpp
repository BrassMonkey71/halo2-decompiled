// @flags /O2 /GL-
// Havok (third-party physics library): starting a query of a tree of cells
// for the keys of the cells a pair of bounds touches, the bounds taken into
// the tree's fixed-point grid.
#include <xmmintrin.h>

struct s_surface_key_array;

struct s_query_bounds
{
	__m128 minimum, maximum;
};

// a value rounded to the nearest integer by the FPU
__forceinline int round_300150(float value)
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
struct tree_300150
{
	float origin[3];
	float scale;
	char unknown10[0x30 - 0x10];
	unsigned char nodes[1];
};

// a range of cells, in whole cells, and the walk's state
struct __declspec(align(16)) cell_range_2ff8b0
{
	long upper[3];
	long unknownc;
	long lower[3];
	long unknown1c;
	long field_20;
	long field_24;
	long field_28;
	long field_2c;
	long field_30;
	long field_34;
};

class class_300150
{
public:
	s_surface_key_array *keys;
	long unknown4[3];
	long upper[3];
	long unknown1c;
	long lower[3];
	long unknown2c;
	tree_300150 const *tree;

	void function_300150(void const *tree, const s_query_bounds *bounds, s_surface_key_array *keys);
	void function_2ff8b0(cell_range_2ff8b0 const *range, unsigned char const *node);
};

// the bounds' corners in the tree's fixed-point grid, and the walk of the
// tree from its root
// @retail 0x300150
void class_300150::function_300150(void const *tree_, const s_query_bounds *bounds, s_surface_key_array *keys_)
{
	keys = keys_;
	tree = (tree_300150 const *)tree_;
	float const *minimum = (float const *)&bounds->minimum;
	float const *maximum = (float const *)&bounds->maximum;
	lower[0] = round_300150((minimum[0] - tree->origin[0]) * tree->scale) - 1;
	upper[0] = round_300150((maximum[0] - tree->origin[0]) * tree->scale) - 1;
	lower[1] = round_300150((minimum[1] - tree->origin[1]) * tree->scale) - 1;
	upper[1] = round_300150((maximum[1] - tree->origin[1]) * tree->scale) - 1;
	lower[2] = round_300150((minimum[2] - tree->origin[2]) * tree->scale) - 1;
	upper[2] = round_300150((maximum[2] - tree->origin[2]) * tree->scale) - 1;
	cell_range_2ff8b0 range;
	range.lower[0] = lower[0] >> 16;
	range.upper[0] = (upper[0] >> 16) + 1;
	range.lower[1] = lower[1] >> 16;
	range.upper[1] = (upper[1] >> 16) + 1;
	range.lower[2] = lower[2] >> 16;
	range.upper[2] = (upper[2] >> 16) + 1;
	range.field_20 = 0;
	range.field_24 = 0;
	range.field_28 = 0;
	range.field_2c = 0;
	range.field_30 = 0;
	range.field_34 = 0;
	function_2ff8b0(&range, ((tree_300150 const *)tree_)->nodes);
}
