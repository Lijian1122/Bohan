/*
 * @Author: bohan.lj
 * @Date: 2022-11-05 22:08:34
 * @FilePath: /Bohan/bohan/base/Util.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-05 23:04:23
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
#ifdef __cplusplus
extern "C" {
#endif
uint64_t get_current_tick();
#ifdef __cplusplus
}
#endif

}
#endif