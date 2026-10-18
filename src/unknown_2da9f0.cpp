// @flags /O2 /GL- /GX
// Havok (third-party physics library): an object that listens to a world
// through two interfaces, and detaches both from the world when the world
// lets it go or when it is destroyed.
#include "reference_counted_2d88a0.h"

bool __cdecl function_279740(long value);

class listener_30c420;

class c_library_30c470
{
public:
	void detach(void *callback);
};

class class_30c420
{
public:
	void function_30c420(listener_30c420 *listener);
};

class deletable_2da9f0
{
public:
	virtual void destroy(unsigned int flags) = 0;
};

class interface_b_2da9f0
{
public:
	virtual void slot_0(void *arg);
	virtual void slot_1() {}
	virtual void slot_2() {}
};

class interface_c_2da9f0
{
public:
	virtual ~interface_c_2da9f0() {}
	virtual void released(void *world) = 0;
};

class class_2da9f0 : public referenced_2d88a0, public interface_b_2da9f0, public interface_c_2da9f0
{
public:
	REFERENCED_NEW_2D88A0(0xb)

	void *world;

	~class_2da9f0();
	void released(void *world_);
};

// @retail 0x2da9f0
void class_2da9f0::released(void *world_)
{
	((c_library_30c470 *)world)->detach(static_cast<interface_c_2da9f0 *>(this));
	((class_30c420 *)world)->function_30c420((listener_30c420 *)static_cast<interface_b_2da9f0 *>(this));
	world = 0;
	referenced_2d88a0 *object = this;
	object->reference_count--;
	if (object->reference_count == 0)
	{
		if (function_279740((long)object))
		{
			object->reference_count = 1;
		}
		else
		{
			((deletable_2da9f0 *)object)->destroy(1);
		}
	}
}

// @retail 0x2daa60
class_2da9f0::~class_2da9f0()
{
	if (world)
	{
		((c_library_30c470 *)world)->detach(static_cast<interface_c_2da9f0 *>(this));
		((class_30c420 *)world)->function_30c420((listener_30c420 *)static_cast<interface_b_2da9f0 *>(this));
	}
}
