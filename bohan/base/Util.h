/*
 * @Author: bohan.lj
 * @Date: 2022-11-05 22:08:34
 * @FilePath: /Bohan/bohan/base/Util.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-11 11:19:22
 * @Description: srouce_code
 */


#ifndef BOHAN_BASE_UTIL_H
#define BOHAN_BASE_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#else
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#endif
#include "os_type.h"

namespace bohan{

typedef struct DateTimeEntity{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    int ms;
};

#ifdef _MSC_VER
struct timezone {
    int tz_minuteswest; /* of Greenwich */
    int tz_dsttime;     /* type of dst correction to apply */
};

#include <sys/timeb.h>
int gettimeofday(struct timeval *tv, struct timezone *tz) {
    struct _timeb tb;
    _ftime(&tb);
    if (tv) {
        tv->tv_sec =  (long)tb.time;
        tv->tv_usec = tb.millitm * 1000;
    }
    if (tz) {
        tz->tz_minuteswest = tb.timezone;
        tz->tz_dsttime = tb.dstflag;
    }
    return 0;
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
uint64_t get_current_tick();
unsigned long long gettime_forday_ms();
unsigned long long gettime_forday_us();
DateTimeEntity gettime_now();
char* datetime_fmt(DateTimeEntity* dt, char* buf);
char* datetime_fmt_ms(DateTimeEntity* dt, char* buf);
#ifdef __cplusplus
}
#endif
}
#endif