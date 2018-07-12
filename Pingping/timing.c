#include "timing.h"

#ifdef _WIN32

#include <Windows.h>

double current_time_ms(void)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	return time.QuadPart / (freq.QuadPart / 1000.0);
}

#endif
