// @flags /O2 /GL-
// Havok (third-party physics library): returns its third argument offset
// by 0x80 bytes; the first two arguments are unused.

struct class_31a6a0
{
    char *function_31a6a0(long arg_0, long arg_1, char *base);
};

// @retail 0x31a6a0
char *class_31a6a0::function_31a6a0(long arg_0, long arg_1, char *base)
{
    return base + 0x80;
}
