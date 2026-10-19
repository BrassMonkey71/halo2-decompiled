// @flags /O2 /GL-
// Havok (third-party physics library): adds a point mass's contribution to
// a 3x3 inertia tensor stored in rows of four floats.

// @retail 0x2db9e0
void __cdecl function_2db9e0(float const *point, float mass, float *inertia)
{
	inertia[0] += (point[1] * point[1] + point[2] * point[2]) * mass;
	inertia[5] += (point[0] * point[0] + point[2] * point[2]) * mass;
	inertia[10] += (point[0] * point[0] + point[1] * point[1]) * mass;
	inertia[1] -= mass * point[0] * point[1];
	inertia[4] = inertia[1];
	inertia[6] -= mass * point[2] * point[1];
	inertia[9] = inertia[6];
	inertia[8] -= mass * point[0] * point[2];
	inertia[2] = inertia[8];
}
