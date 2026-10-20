// @flags /O2 /GL-
// Havok (third-party physics library): the bounds of a box under a transform,
// grown by the box's radius and a tolerance (through the game's 0x1ce210).
#include <xmmintrin.h>

void __cdecl function_1ce210(const __m128 *matrix, const __m128 *extent,
	const __m128 *center, float expansion, __m128 *output);

class box_2fd8a0
{
public:
	char unknown0[0xc];
	float radius;
	__m128 extent;
	__m128 center;

	void function_2fd8a0(const __m128 *matrix, float tolerance, __m128 *output) const;
};

// @retail 0x2fd8a0
void box_2fd8a0::function_2fd8a0(const __m128 *matrix, float tolerance, __m128 *output) const
{
	function_1ce210(matrix, &extent, &center, tolerance + radius, output);
}
