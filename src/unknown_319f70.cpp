// @flags /O2 /GL-
// Havok (third-party physics library): a rigid motion's step: the velocities
// kept, the position moved by the linear velocity, the rotation turned by the
// angular velocity (the angle turned kept in the old position's last lane)
// and normalized, and the transform rebuilt from them.
#include "derived_311920.h"

// the game's quaternion normalization (src/unknown_1d8d60.cpp)
struct s_1d8d60
{
	__m128 field_0;
	void function_1d8d60();
};

class quaternion_319300
{
public:
	__m128 vector;

	// this = a * b
	void function_319300(quaternion_319300 const &a, quaternion_319300 const &b);
};

// the first three lanes
static __declspec(align(16)) const unsigned long g_415120[4] = {0xffffffff, 0xffffffff, 0xffffffff, 0};

// all four lanes set to one value
inline __m128 broadcast_319f70(float value)
{
	__m128 single = _mm_set_ss(value);
	return _mm_shuffle_ps(single, single, 0);
}

// a vector turned by a rotation matrix
inline __m128 rotate_319f70(rotation_372500 const &rotation, __m128 const &vector)
{
	__m128 z = _mm_mul_ps(rotation.column[2], _mm_shuffle_ps(vector, vector, 0xaa));
	__m128 y = _mm_mul_ps(rotation.column[1], _mm_shuffle_ps(vector, vector, 0x55));
	__m128 x = _mm_mul_ps(rotation.column[0], _mm_shuffle_ps(vector, vector, 0));
	return _mm_add_ps(_mm_add_ps(x, y), z);
}

class motion_319f70 : public class_3114d0
{
public:
	char unknownc0[0xe0 - 0xc0];
	__m128 saved_40;
	__m128 saved_50;

	void function_319f70(float const *step);
};

// @retail 0x319f70
void motion_319f70::function_319f70(float const *step)
{
	saved_40 = field_40;
	saved_50 = field_50;
	field_60 = field_70;
	field_70 = _mm_add_ps(field_70, _mm_mul_ps(broadcast_319f70(*step), field_40));
	__m128 squares = _mm_mul_ps(field_50, field_50);
	__m128 sum = _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa),
		_mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares));
	float speed;
	_mm_store_ss(&speed, _mm_sqrt_ss(sum));
	field_60.m128_f32[3] = field_c * *step * speed;
	quaternion_319300 spin;
	spin.vector = _mm_and_ps(_mm_mul_ps(broadcast_319f70(0.5f), field_50), *(__m128 const *)g_415120);
	quaternion_319300 change;
	change.function_319300(spin, *(quaternion_319300 const *)&rotation);
	rotation = _mm_add_ps(rotation, _mm_mul_ps(broadcast_319f70(*step), change.vector));
	((s_1d8d60 *)&rotation)->function_1d8d60();
	transform_rotation.function_372500(&rotation);
	transform_translation = _mm_sub_ps(field_70, rotate_319f70(transform_rotation, field_20));
	field_70.m128_f32[3] = 1.0f;
}
