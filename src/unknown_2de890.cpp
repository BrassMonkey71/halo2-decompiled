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
	float function_2de8e0(__m128 const &direction) const;
};

// the child seen through its vtable: slot 7 takes a direction in the child's
// own frame and gives back a distance along it
class child_slots_2de8e0
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual void slot_5() {}
	virtual void slot_6() {}
	virtual float slot_7(__m128 const *direction) { return 0.0f; }
};

// @retail 0x2de890
c_child_transform::c_child_transform(c_havok_reference_counted *child_)
	: child(child_)
{
	transform.load_unit_columns();
	child->reference_count++;
}

// the direction taken into the child's frame (the transposed axes), the
// child's distance along it, and that point placed back by the transform and
// measured along the direction
// @retail 0x2de8e0
float c_child_transform::function_2de8e0(__m128 const &direction) const
{
	__m128 row0 = transform.columns[0];
	__m128 row1 = transform.columns[1];
	__m128 row2 = transform.columns[2];
	__m128 row3 = row2;
	_MM_TRANSPOSE4_PS(row0, row1, row2, row3);
	__m128 const d = direction;
	__m128 local = _mm_add_ps(_mm_add_ps(
		_mm_mul_ps(row0, _mm_shuffle_ps(d, d, 0x00)),
		_mm_mul_ps(row1, _mm_shuffle_ps(d, d, 0x55))),
		_mm_mul_ps(row2, _mm_shuffle_ps(d, d, 0xaa)));
	__m128 const single = _mm_set_ss(((child_slots_2de8e0 *)child)->slot_7(&local));
	__m128 const scaled = _mm_mul_ps(_mm_shuffle_ps(single, single, 0), local);
	__m128 const point = _mm_add_ps(_mm_add_ps(
		_mm_mul_ps(transform.columns[0], _mm_shuffle_ps(scaled, scaled, 0x00)),
		_mm_mul_ps(transform.columns[1], _mm_shuffle_ps(scaled, scaled, 0x55))),
		_mm_add_ps(_mm_mul_ps(transform.columns[2], _mm_shuffle_ps(scaled, scaled, 0xaa)), transform.columns[3]));
	__m128 const product = _mm_mul_ps(point, direction);
	float result;
	_mm_store_ss(&result, _mm_add_ss(_mm_shuffle_ps(product, product, 0xaa), _mm_add_ss(_mm_shuffle_ps(product, product, 0x55), product)));
	return result;
}
