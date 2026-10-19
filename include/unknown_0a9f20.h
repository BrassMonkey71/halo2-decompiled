/* UNKNOWN_0A9F20.H: a reference object (vtable 0x452c1c) over a base (vtable
   0x452c30) that frees itself to the allocator at 0x480118 with the size it
   keeps in its first word; several Havok classes derive from it, the capsule
   0x2de0a0 builds (vtable 0x455458) among them */
#pragma once

#include "globals.h"

class c_sized_reference
{
public:
    virtual ~c_sized_reference() {}
    word flags;
    word unknown06;

    static void operator delete(void *block)
    {
        g_480118->allocate((long)block, ((c_sized_reference *)block)->flags, 0x10);
    }
};

class c_reference_a9f20 : public c_sized_reference
{
public:
    virtual ~c_reference_a9f20();
};

/* a capsule between two points; destroying one runs only the reference
   object's destructor (0xdc370) */
class __declspec(align(16)) c_z_capsule_temp : public c_reference_a9f20
{
public:
    c_z_capsule_temp(void const *first, void const *second, real radius);
    byte unknown08[0x28];
};
