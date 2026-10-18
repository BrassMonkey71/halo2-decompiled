// @flags /O2 /GL-
// Havok (third-party physics library): increments the counter at offset
// 0x24.

struct class_3009b0
{
    char unknown0[0x24];
    long field_24;

    void function_3009b0();
};

// @retail 0x3009b0
void class_3009b0::function_3009b0()
{
    field_24++;
}
