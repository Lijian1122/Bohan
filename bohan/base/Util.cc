/*
 * @Author: bohan.lj
 * @Date: 2022-11-05 22:08:50
 * @FilePath: /Bohan/bohan/base/Util.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-05 23:02:01
 * @Description: srouce_code
 */
#include "Util.h"

namespace bohan
{
uint64_t get_current_tick()
{
#ifdef _MSC_VER
	LARGE_INTEGER liCounter; 
	LARGE_INTEGER liCurrent;
	if (!QueryPerformanceFrequency(&liCounter))
		return GetTickCount();

	QueryPerformanceCounter(&liCurrent);
	return (uint64_t)(liCurrent.QuadPart * 1000 / liCounter.QuadPart);
#else
	struct timeval tval;
	uint64_t current_tick;

	gettimeofday(&tval, NULL);

	current_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
	return current_tick;
#endif
}
}
