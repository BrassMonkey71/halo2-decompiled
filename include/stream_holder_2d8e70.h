#ifndef STREAM_HOLDER_2D8E70_H
#define STREAM_HOLDER_2D8E70_H
// Havok (third-party physics library): a stream over another stream, holding
// a reference to the stream beneath it. Its constructor leaves the reference
// count alone, so its base has no constructor of its own.
#include "reference_counted_2d88a0.h"

class stream_base_2d8e70
{
public:
	unsigned short memory_size;
	unsigned short reference_count;

	virtual ~stream_base_2d8e70() {}
};

class stream_holder_2d8e70 : public stream_base_2d8e70
{
public:
	REFERENCED_NEW_2D88A0(0x15)

	referenced_2d88a0 *stream;

	stream_holder_2d8e70(char *buffer, long size, bool zero);
	~stream_holder_2d8e70();
};

#endif
