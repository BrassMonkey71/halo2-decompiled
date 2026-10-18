#ifndef PLACED_CHILD_2DEC70_H
#define PLACED_CHILD_2DEC70_H
// Havok (third-party physics library): an object that places a child object
// by a 3x4 transform of SSE columns, holding a reference to the child.
#include "shape_2de750.h"
#include "havok_reference.h"

struct child_info_2dec70 : shape_info_2de750
{
	c_havok_reference_counted *child;
	long unknown8;
	long unknownc;
	__m128 transform[4];
};

class placed_child_2dec70 : public shape_2de750
{
public:
	c_havok_reference_counted *child;
	__m128 transform[4];

	placed_child_2dec70(child_info_2dec70 const &info);
};

#endif
