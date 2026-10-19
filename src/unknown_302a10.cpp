// @flags /O2 /GL-
// Havok (third-party physics library): cutting five contact points down to
// the four that span the most: the point farthest from the first, the point
// farthest from that, the point farthest from the line through those two, and
// the point farthest from that; the one left over is handed back to its owner
// and replaced by the last.
#include <xmmintrin.h>

struct point_302a10
{
	__m128 position;
	union
	{
		__m128 normal;
		struct
		{
			float normal_xyz[3];
			unsigned short id;
		};
	};
	__m128 field_20;
};

class owner_302a10
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void release_id(unsigned short id) {}
};

// the squared length of a vector's first three terms
inline float length_squared_302a10(__m128 v)
{
	__m128 squares = _mm_mul_ps(v, v);
	float result;
	_mm_store_ss(&result, _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares)));
	return result;
}

// the cross product of two vectors' first three terms
inline __m128 cross_302a10(__m128 const &a, __m128 const &b)
{
	return _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(a, a, 0xc9), _mm_shuffle_ps(b, b, 0xd2)),
		_mm_mul_ps(_mm_shuffle_ps(a, a, 0xd2), _mm_shuffle_ps(b, b, 0xc9)));
}

// @retail 0x302a10
void __cdecl function_302a10(point_302a10 **points, void *arg_1, void *arg_2, owner_302a10 *owner)
{
	bool used[5];
	for (int k = 0; k < 5; k++)
	{
		used[k] = false;
	}
	int count = 5;
	int best = 0;

	point_302a10 const *first = points[0];
	float largest = 0.0f;
	for (int i = 0; i < 5; i++)
	{
		if (!used[i] && i != best)
		{
			float distance = length_squared_302a10(_mm_sub_ps(first->position, points[i]->position));
			if (distance > largest)
			{
				largest = distance;
				best = i;
			}
		}
	}
	int second_index = best;
	used[best] = true;

	point_302a10 const *second = points[second_index];
	largest = 0.0f;
	for (int i = 0; i < 5; i++)
	{
		if (!used[i])
		{
			float distance = length_squared_302a10(_mm_sub_ps(second->position, points[i]->position));
			if (distance > largest)
			{
				largest = distance;
				best = i;
			}
		}
	}
	used[best] = true;

	point_302a10 const *third = points[best];
	__m128 edge = _mm_sub_ps(points[second_index]->position, third->position);
	largest = 0.0f;
	for (int i = 0; i < 5; i++)
	{
		if (!used[i])
		{
			float distance = length_squared_302a10(cross_302a10(_mm_sub_ps(third->position, points[i]->position), edge));
			if (distance > largest)
			{
				largest = distance;
				best = i;
			}
		}
	}
	used[best] = true;

	point_302a10 const *fourth = points[best];
	largest = 0.0f;
	for (int i = 0; i < 5; i++)
	{
		if (!used[i])
		{
			float distance = length_squared_302a10(_mm_sub_ps(fourth->position, points[i]->position));
			if (distance > largest)
			{
				largest = distance;
				best = i;
			}
		}
	}
	used[best] = true;

	for (int i = 0; i < count;)
	{
		if (!used[i])
		{
			owner->release_id(points[i]->id);
			*points[i] = *points[count - 1];
			used[i] = used[count - 1];
			count--;
		}
		else
		{
			i++;
		}
	}
}
