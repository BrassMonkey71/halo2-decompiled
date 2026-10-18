// @flags /O2 /GL-
// Havok (third-party physics library): the destructor of a class with a
// vtable (0x41387c) and nothing to release.

class class_30c640
{
public:
    ~class_30c640();
    virtual void v0() = 0;
};

// @retail 0x30c640
class_30c640::~class_30c640()
{
}
