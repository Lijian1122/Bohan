/*
 * @Author: bohan.lj
 * @Date: 2022-11-05 22:08:50
 * @FilePath: /Bohan/bohan/base/Util.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-10 22:57:19
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

unsigned long long gettime_forday_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (unsigned long long)1000 + tv.tv_usec/1000;	
}
unsigned long long gettime_forday_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (unsigned long long)1000000 + tv.tv_usec;
}

DateTimeEntity gettime_now()
{
    DateTimeEntity  date;
#ifdef OS_WIN
    SYSTEMTIME tm;
    GetLocalTime(&tm);
    date.year     = tm.wYear;
    date.month    = tm.wMonth;
    date.day      = tm.wDay;
    date.hour     = tm.wHour;
    date.min      = tm.wMinute;
    date.sec      = tm.wSecond;
    date.ms       = tm.wMilliseconds;
#else
    struct timeval tv;
    struct tm* tm = NULL;
    gettimeofday(&tv, NULL);
    time_t tt = tv.tv_sec;
    tm = localtime(&tt);
    date.year     = tm->tm_year + 1900;
    date.month    = tm->tm_mon  + 1;
    date.day      = tm->tm_mday;
    date.hour     = tm->tm_hour;
    date.min      = tm->tm_min;
    date.sec      = tm->tm_sec;
    date.ms       = tv.tv_usec/1000;
#endif
    return date;
}

char* datetime_fmt(DateTimeEntity* dt, char* buf)
{
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
        dt->year, dt->month, dt->day,
        dt->hour, dt->min, dt->sec);
    return buf;
}
char* datetime_fmt_ms(DateTimeEntity* dt, char* buf)
{
    sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d.%03dZ",
        dt->year, dt->month, dt->day,
        dt->hour, dt->min, dt->sec,
        dt->ms);
    return buf;
}
}
