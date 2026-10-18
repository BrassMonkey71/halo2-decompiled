// @flags /O2 /GL-
// Havok (third-party physics library): whether a dispatcher's table holds
// the creation function at 0x2dae40 for a pair of kinds, or else the one the
// test at 0x2f98a0 looks for.

struct result_2f98a0
{
	char value;

	result_2f98a0(bool value_) : value((char)value_) {}
};

typedef void *(__cdecl *create_function_2f98a0)(long arg_0, long arg_1, long arg_2, long value);

void *__cdecl function_2dae40(long arg_0, long arg_1, long arg_2, long value);

struct dispatcher_2f98a0
{
	char unknown0[0x18c];
	create_function_2f98a0 functions[32][32];
};

result_2f98a0 __cdecl function_2f98a0(dispatcher_2f98a0 const *dispatcher, long first, long second);

// @retail 0x2daec0
result_2f98a0 __cdecl function_2daec0(dispatcher_2f98a0 const *dispatcher, long first, long second)
{
	if (dispatcher->functions[first][second] == function_2dae40)
	{
		return true;
	}
	return function_2f98a0(dispatcher, first, second);
}
