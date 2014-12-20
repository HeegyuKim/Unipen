
#ifndef _utils_h_
#define _utils_h_


#include <Windows.h>


inline int RandomInt(int minValue, int maxValue)
{
	return (rand() % (maxValue - minValue)) + minValue;
}

inline float RandomFloat()
{
	return (rand() / (float)RAND_MAX);
}

inline float RandomFloat(float minValue, float maxValue)
{
	return RandomFloat() * (maxValue - minValue) + minValue;
}

inline bool IsKeyDown(UINT keyCode)
{
	return (bool)(GetAsyncKeyState(keyCode) & 0x8000);
}

inline float Clamp(float val, float minValue, float maxValue)
{
	if(val < minValue)
		return minValue;
	else if(val > maxValue)
		return maxValue;
	else
		return val;
}

inline bool IsIntersect(
	const D2D1_RECT_F& a,
	const D2D1_RECT_F& b )
{
	return a.right > b.left &&
		b.right > a.left &&
			a.bottom > b.top &&
			b.bottom > a.top;
}
		
#endif