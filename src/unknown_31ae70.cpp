// @flags /O2 /GL-
// Havok (third-party physics library): impulses on a body: one at a point,
// changing both velocities, and a turning one, changing the angular velocity
// through the inverse inertia held in the body's frame.
#include <xmmintrin.h>

// a vector of four copies of a float
inline __m128 splat_31ae70(float value)
{
	__m128 const single = _mm_set_ss(value);
	return _mm_shuffle_ps(single, single, 0);
}

// a vector updated in place
struct vector_31ae70
{
	__m128 value;

	void add_product(__m128 const &a, __m128 const &b) { value = _mm_add_ps(value, _mm_mul_ps(a, b)); }
	void add(__m128 const &a) { value = _mm_add_ps(value, a); }
};

class body_31ae70
{
public:
	char unknown0[0x2c];
	float inverse_mass;
	char unknown30[0x10];
	vector_31ae70 linear_velocity;
	vector_31ae70 angular_velocity;
	char unknown60[0x10];
	__m128 centre;
	__m128 axes[3];
	char unknownb0[0x30];
	__m128 inverse_inertia;

	void function_31ae70(__m128 const *impulse, __m128 const *point);
	void function_31af90(__m128 const *impulse);

};

// @retail 0x31ae70
void body_31ae70::function_31ae70(__m128 const *impulse, __m128 const *point)
{
	linear_velocity.add_product(splat_31ae70(inverse_mass), *impulse);
	__m128 const arm = _mm_sub_ps(*point, centre);
	__m128 const p = *impulse;
	__m128 const torque = _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(arm, arm, 0xc9), _mm_shuffle_ps(p, p, 0xd2)),
		_mm_mul_ps(_mm_shuffle_ps(arm, arm, 0xd2), _mm_shuffle_ps(p, p, 0xc9)));
	__m128 row0 = axes[0];
	__m128 row1 = axes[1];
	__m128 row2 = axes[2];
	__m128 row3 = row2;
	_MM_TRANSPOSE4_PS(row0, row1, row2, row3);
	__m128 const local = _mm_add_ps(_mm_add_ps(
		_mm_mul_ps(row0, _mm_shuffle_ps(torque, torque, 0x00)),
		_mm_mul_ps(row1, _mm_shuffle_ps(torque, torque, 0x55))),
		_mm_mul_ps(row2, _mm_shuffle_ps(torque, torque, 0xaa)));
	__m128 const scaled = _mm_mul_ps(inverse_inertia, local);
	__m128 const turn = _mm_add_ps(_mm_add_ps(
		_mm_mul_ps(_mm_load_ps(axes[0].m128_f32), _mm_shuffle_ps(scaled, scaled, 0x00)),
		_mm_mul_ps(_mm_load_ps(axes[1].m128_f32), _mm_shuffle_ps(scaled, scaled, 0x55))),
		_mm_mul_ps(_mm_load_ps(axes[2].m128_f32), _mm_shuffle_ps(scaled, scaled, 0xaa)));
	angular_velocity.add(turn);
}
// @retail 0x31af90
void body_31ae70::function_31af90(__m128 const *impulse)
{
	__m128 row0 = axes[0];
	__m128 row1 = axes[1];
	__m128 row2 = axes[2];
	__m128 row3 = row2;
	_MM_TRANSPOSE4_PS(row0, row1, row2, row3);
	__m128 const torque = *impulse;
	__m128 const local = _mm_add_ps(_mm_add_ps(
		_mm_mul_ps(row0, _mm_shuffle_ps(torque, torque, 0x00)),
		_mm_mul_ps(row1, _mm_shuffle_ps(torque, torque, 0x55))),
		_mm_mul_ps(row2, _mm_shuffle_ps(torque, torque, 0xaa)));
	__m128 const scaled = _mm_mul_ps(inverse_inertia, local);
	__m128 const turn = _mm_add_ps(_mm_add_ps(
		_mm_mul_ps(_mm_load_ps(axes[0].m128_f32), _mm_shuffle_ps(scaled, scaled, 0x00)),
		_mm_mul_ps(_mm_load_ps(axes[1].m128_f32), _mm_shuffle_ps(scaled, scaled, 0x55))),
		_mm_mul_ps(_mm_load_ps(axes[2].m128_f32), _mm_shuffle_ps(scaled, scaled, 0xaa)));
	angular_velocity.add(turn);
}
