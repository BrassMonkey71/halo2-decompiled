// @flags /O2 /GL-
// Havok (third-party physics library): a step of an iterative solver: asks
// for the response against the reversed direction, accumulates it, offsets
// the accumulated value by the reciprocal scales, and returns the response
// reversed.
#include <xmmintrin.h>

static __declspec(align(16)) const unsigned long g_4124a0[4] = {0x80000000, 0x80000000, 0x80000000, 0x80000000};

class solver_2e0120
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual void slot_5() {}
	virtual void slot_6() {}
	virtual void slot_7() {}
	virtual void slot_8() {}
	virtual void slot_9() {}
	virtual void respond(__m128 const *direction, __m128 *out, void *context) {}

	__m128 accumulated; // at 0x10: the vtable pointer is padded to the vector alignment
	__m128 offset;
	float scale[3];

	void function_2e0120(__m128 const *direction, __m128 *out, void *context);
};

// @retail 0x2e0120
void solver_2e0120::function_2e0120(__m128 const *direction, __m128 *out, void *context)
{
	__m128 const sign = *(__m128 const *)g_4124a0;
	__m128 reversed = _mm_xor_ps(*direction, sign);
	__m128 response;
	respond(&reversed, &response, context);
	_mm_store_ps((float *)&accumulated, _mm_add_ps(accumulated, response));
	__m128 reciprocal;
	((float *)&reciprocal)[0] = 1.0f / scale[0];
	((float *)&reciprocal)[1] = 1.0f / scale[1];
	((float *)&reciprocal)[2] = 1.0f / scale[2];
	((float *)&reciprocal)[3] = 0.0f;
	offset = _mm_add_ps(accumulated, reciprocal);
	*out = _mm_xor_ps(response, *(__m128 const *)g_4124a0);
}
