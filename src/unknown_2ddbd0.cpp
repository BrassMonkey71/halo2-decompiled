// @flags /O2 /GL-
// Havok (third-party physics library): collecting what a sphere touches by
// walking a tree in fixed-point coordinates.
#include <xmmintrin.h>

struct s_visibility_query_list;

// a sphere: its centre, and its radius as the fourth term
struct s_visibility_sphere_query
{
	__m128 centre;
};

// the tree's origin, with the size of one unit as the fourth term, and the
// tree itself at 0x30
struct tree_2ddbd0
{
	__m128 origin;
	char unknown10[0x20];
	char root[1];
};

// the nodes still to visit
struct pending_2ddbd0
{
	long field_0;
	long field_4;
	long field_8;
	long field_c;
	long field_10;
	long field_14;

	pending_2ddbd0()
	{
		field_8 = 0;
		field_c = 0;
		field_10 = 0;
		field_0 = 0;
		field_4 = 0;
		field_14 = 0x10;
	}
};

struct point_2ddbd0
{
	float x;
	float y;
	float z;
};

class class_2dce60
{
public:
	s_visibility_query_list *second;
	char unknown4[0xc];
	float scale;
	char unknown14[0xc];
	s_visibility_query_list *first;
	char unknown24[0xc];
	point_2ddbd0 centre;
	float diameter;
	__m128 offset;
	__m128 fixed_scale;

	void function_2dce60(pending_2ddbd0 *pending, void const *root, __m128 const *offset);
};

// @retail 0x2ddbd0
void __cdecl function_2ddbd0(void *data, s_visibility_sphere_query const *query,
	s_visibility_query_list *second, s_visibility_query_list *first)
{
	tree_2ddbd0 const *tree = (tree_2ddbd0 const *)data;
	class_2dce60 walk;
	walk.scale = 1.0f / tree->origin.m128_f32[3];
	walk.offset = _mm_setzero_ps();
	walk.second = second;
	pending_2ddbd0 pending;
	walk.fixed_scale = _mm_set_ps1(walk.scale * 16777216.0f);
	walk.diameter = query->centre.m128_f32[3] + query->centre.m128_f32[3];
	__m128 const relative = _mm_sub_ps(query->centre, tree->origin);
	__m128 doubled = _mm_add_ps(relative, relative);
	walk.centre.x = doubled.m128_f32[0];
	walk.centre.y = doubled.m128_f32[1];
	walk.centre.z = doubled.m128_f32[2];
	walk.first = first;
	walk.function_2dce60(&pending, tree->root, &walk.offset);
}
