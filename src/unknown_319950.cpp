// @flags /O2 /GL-
// Havok (third-party physics library): copies a body's nine motion vectors
// (from +0x30 to +0xb0) into another object at the same offsets.
#include <xmmintrin.h>

struct motion_state_319950
{
	__m128 vectors[9];
};

class body_319950
{
public:
	char unknown0[0x30];
	motion_state_319950 state;

	void snapshot_into(body_319950 *out) const;
};

// @retail 0x319950
void body_319950::snapshot_into(body_319950 *out) const
{
	out->state.vectors[0] = state.vectors[0];
	out->state.vectors[1] = state.vectors[1];
	out->state.vectors[2] = state.vectors[2];
	out->state.vectors[3] = state.vectors[3];
	out->state.vectors[4] = state.vectors[4];
	out->state.vectors[5] = state.vectors[5];
	out->state.vectors[6] = state.vectors[6];
	out->state.vectors[7] = state.vectors[7];
	out->state.vectors[8] = state.vectors[8];
}
