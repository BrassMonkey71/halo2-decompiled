// @flags /O2 /GL-
// Havok (third-party physics library): a query of a shape holding a tree of
// parts against the child of a wrapping shape, into the caller's collector.
#include "child_query_2f9950.h"

// @retail 0x2fabf0
void __cdecl function_2fabf0(body_2ea940 const *a, body_2ea940 const *b, input_2ea940 const *input, void *collector)
{
	wrapper_2f9950 const *wrapper = (wrapper_2f9950 const *)b->shape;
	void const *placement = b->placement;
	body_2ea940 child;
	child.placement = placement;
	child.parent = b;
	child.shape = wrapper->child;
	child.key = b->key;
	function_2ea940(a, &child, input, collector);
}
