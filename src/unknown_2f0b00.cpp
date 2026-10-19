// @flags /O2 /GL- /GX
// Havok (third-party physics library): the sphere-capsule pair test run in
// either order, the reversed order reporting through a collector that swaps
// each pair back.
#include "pair_collector_2f09b0.h"

// a collector that hands each pair on to another one with its bodies swapped
class swapping_collector_2f0b20 : public collector_2f09b0
{
public:
	collector_2f09b0 *target;

	swapping_collector_2f0b20(collector_2f09b0 *target_collector)
	{
		target = target_collector;
	}
	virtual ~swapping_collector_2f0b20() {}
	virtual void add_pair(body_2f09b0 const *first, body_2f09b0 const *second)
	{
		target->add_pair(second, first);
	}
};

class pair_test_2f0b00
{
public:
	void function_2f0b00(body_2f09b0 const *sphere_body, body_2f09b0 const *capsule_body, void const *input, collector_2f09b0 *collector);
	void function_2f0b20(body_2f09b0 const *capsule_body, body_2f09b0 const *sphere_body, void const *input, collector_2f09b0 *collector);
};

// @retail 0x2f0b00
void pair_test_2f0b00::function_2f0b00(body_2f09b0 const *sphere_body, body_2f09b0 const *capsule_body, void const *input, collector_2f09b0 *collector)
{
	function_2f09b0(sphere_body, capsule_body, input, collector);
}

// @retail 0x2f0b20
void pair_test_2f0b00::function_2f0b20(body_2f09b0 const *capsule_body, body_2f09b0 const *sphere_body, void const *input, collector_2f09b0 *collector)
{
	swapping_collector_2f0b20 swapped(collector);
	function_2f09b0(sphere_body, capsule_body, input, &swapped);
}

// @retail 0x2f0b80
void __cdecl function_2f0b80(body_2f09b0 const *capsule_body, body_2f09b0 const *sphere_body, void const *input, collector_2f09b0 *collector)
{
	swapping_collector_2f0b20 swapped(collector);
	function_2f09b0(sphere_body, capsule_body, input, &swapped);
}
