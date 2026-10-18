// @flags /O2 /GL-
// Havok (third-party physics library): an object placing a child object by
// a transform, constructed from the child alone with the identity transform.
#include "shape_2de750.h"
#include "havok_reference.h"

// a 3x4 transform of SSE columns
struct transform_2de890
{
	__m128 columns[4];

	void load_unit_columns()
	{
		__m128 zero = _mm_setzero_ps();
		columns[0] = zero;
		columns[1] = zero;
		columns[2] = zero;
		float *elements = (float *)columns;
		elements[0] = 1.0f;
		elements[5] = 1.0f;
		elements[10] = 1.0f;
		columns[3] = zero;
	}
};

// the declaration game code calls (src/unknown_1ee340.cpp)
class c_child_transform : public shape_2de750
{
public:
	c_havok_reference_counted *child;
	transform_2de890 transform;

	c_child_transform(c_havok_reference_counted *child);
};

// @retail 0x2de890
c_child_transform::c_child_transform(c_havok_reference_counted *child_)
	: child(child_)
{
	transform.load_unit_columns();
	child->reference_count++;
}
