// @flags /O2 /GL-
// Havok (third-party physics library): walking from face to face across a
// hull's triangles, leaving each face by an edge that the point lies outside
// of, until no edge leads on or a face is reached twice.
#include <xmmintrin.h>

struct face_30aac0;

struct edge_30aac0
{
	__m128 const *vertex;
	edge_30aac0 const *next;
	edge_30aac0 const *twin;
	face_30aac0 *face;
};

struct face_30aac0
{
	__m128 normal;
	float distance;
	edge_30aac0 edges[3];
	char mark;
};

class class_30a810
{
public:
	void clear_marks();
	face_30aac0 *function_30aac0(face_30aac0 *start);
};

// @retail 0x30aac0
face_30aac0 *class_30a810::function_30aac0(face_30aac0 *start)
{
	clear_marks();
	face_30aac0 *face = start;
	edge_30aac0 const *entered = 0;
	bool done = false;
	while (!done)
	{
		face->mark = 3;
		int i;
		edge_30aac0 const *edge = face->edges;
		for (i = 0; i < 3; i++, edge++)
		{
			if (edge == entered)
			{
				continue;
			}
			__m128 const a = *edge->vertex;
			__m128 const d = _mm_sub_ps(*edge->next->vertex, a);
			__m128 const n = face->normal;
			__m128 const c = _mm_sub_ps(
				_mm_mul_ps(_mm_shuffle_ps(d, d, 0xc9), _mm_shuffle_ps(n, n, 0xd2)),
				_mm_mul_ps(_mm_shuffle_ps(d, d, 0xd2), _mm_shuffle_ps(n, n, 0xc9)));
			__m128 const p = _mm_mul_ps(c, a);
			float side;
			_mm_store_ss(&side, _mm_add_ss(_mm_shuffle_ps(p, p, 0xaa), _mm_add_ss(_mm_shuffle_ps(p, p, 0x55), p)));
			if (side < -1e-4f)
			{
				face_30aac0 *neighbour = edge->twin->face;
				if (!(start->distance > 0.0f) || !(start->distance * 0.9f > neighbour->distance))
				{
					entered = face->edges[i].twin;
					face = neighbour;
					done = neighbour->mark == 3;
					break;
				}
			}
		}
		if (i == 3)
		{
			break;
		}
	}
	return face;
}
