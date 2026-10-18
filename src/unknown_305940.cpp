// @flags /O2 /GL-
// Havok (third-party physics library): replacing x, y and z with the
// reciprocals of their square roots, and clearing w.
#include <math.h>

// @retail 0x305940
void __cdecl function_305940(float *vector)
{
	for (int i = 0; i < 3; i++)
	{
		vector[i] = 1.0f / (float)sqrt(vector[i] + 1.1920928955078125e-07f);
	}
	vector[3] = 0.0f;
}
