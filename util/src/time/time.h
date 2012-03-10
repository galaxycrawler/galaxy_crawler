/* Copyright (C) 2012-2012 galaxycrawler.org

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/**
 * @namespace galaxy_crawler::util::time
 * @brief     Providing some useful time functions.
 * Change Log:
 */

#ifndef _GALAXY_CRAWLER_UTIL_TIME_TIME_H_
#define _GALAXY_CRAWLER_UTIL_TIME_TIME_H_

#include <sys/time.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string>

namespace galaxy_crawler { namespace util { namespace time {

/// Get current time of usec
inline uint64_t rdtsc() {
  struct timeval  tv;
  struct timezone tz;
  tz.tz_minuteswest = 0;
  tz.tz_dsttime     = 0;
  gettimeofday(&tv, &tz);
  uint64_t time = tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
  return time;
}

/// Get current time of usec
inline uint64_t GetCurTimeUs() {
  struct timeval  tv;
  struct timezone tz;
  tz.tz_minuteswest = 0;
  tz.tz_dsttime     = 0;
  gettimeofday(&tv, &tz);
  uint64_t time = tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
  return time;
}

/// Get current time of ms
inline uint32_t GetCurTimeMs() {
  struct timeval  tv;
  struct timezone tz;
  tz.tz_minuteswest = 0;
  tz.tz_dsttime = 0;
  gettimeofday(&tv, &tz);
  uint32_t time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  return time;
}

/// Get current time of ms
inline void GetCurTimeMs(uint64_t *ms) {
  struct timeval  tv;
  struct timezone tz;
  tz.tz_minuteswest = 0;
  tz.tz_dsttime = 0;
  gettimeofday(&tv, &tz);
  *ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/// Modify time_t to a hour specified.
inline time_t GetHourTime(time_t time, int hour) {
  struct tm tm_time;
  localtime_r(&time, &tm_time);
  tm_time.tm_hour = hour;
  tm_time.tm_min = 0;
  tm_time.tm_sec = 0;
  time_t hour_time = mktime(&tm_time);
  return hour_time;
}

/// Convert struct tm to str, like '2012-12-21 23:59:59'
inline std::string TmToStr(const tm &tmTime) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           tmTime.tm_year + 1900, tmTime.tm_mon + 1, tmTime.tm_mday,
           tmTime.tm_hour, tmTime.tm_min, tmTime.tm_sec);
  return buf;
}

/// Convert str like '2012-12-21 23:59:59' to struct tm
/// return true if the convert is success, else return false;
inline bool StrToTm(const std::string &strTime, tm &tmTime) {
  sscanf(strTime.c_str(), "%d-%d-%d %d:%d:%d",
         &tmTime.tm_year, &tmTime.tm_mon, &tmTime.tm_mday,
         &tmTime.tm_hour, &tmTime.tm_min, &tmTime.tm_sec);

  // if (!(tmTime.tm_year >= 0 && tmTime.tm_year <= 9999) ||
  //     !(tmTime.tm_mon >= 1 && tmTime.tm_mon <= 12) ||
  //     !(tmTime.tm_mday >=1 && tmTime.tm_mday <= 31) ||
  //     !(tmTime.tm_hour >= 0 && tmTime.tm_hour <= 59) ||
  //     !(tmTime.tm_min >= 0 && tmTime.tm_min <= 59) ||
  //     !(tmTime.tm_sec >= 0 && tmTime.tm_sec <= 59)) {
  //   return false;
  // }

  tmTime.tm_year -= 1900;
  tmTime.tm_mon -=  1;

  struct tm tm_check;
  tm_check.tm_year = tmTime.tm_year;
  tm_check.tm_mon  = tmTime.tm_mon;
  tm_check.tm_mday = tmTime.tm_mday;
  tm_check.tm_hour = tmTime.tm_hour;
  tm_check.tm_min  = tmTime.tm_min;
  tm_check.tm_sec  = tmTime.tm_sec;
  mktime(&tm_check);
  if (tmTime.tm_year != tm_check.tm_year ||
      tmTime.tm_mon  != tm_check.tm_mon ||
      tmTime.tm_mday != tm_check.tm_mday ||
      tmTime.tm_hour != tm_check.tm_hour ||
      tmTime.tm_min  != tm_check.tm_min ||
      tmTime.tm_sec  != tm_check.tm_sec ) {
    return false;
  }
  return true;
}

/// Convert time_t to tm
inline void TimeToTm(const time_t &tTime, tm &tmTime) {
#ifdef WIN32
  tmTime = *localtime_r(&tTime);
#else
  localtime_r(&tTime, &tmTime);
  bool bGMTZone = false;
  #ifdef  __USE_BSD
  if (strcmp(tmTime.tm_zone, "GMT") == 0)
    bGMTZone = true;
  #else
  if (strcmp(tmTime.__tm_zone, "GMT") == 0)
    bGMTZone = true;
  #endif
  // if (bGMTZone)
  //   AppendFile("./SysAlarm.log","系统严重错误:时区被改成GMT!\n");
#endif
}

/// Convert tm to time_t
inline time_t TmToTime(tm &tmTime) {
  time_t tTime = mktime(&tmTime);
  return tTime;
}

/// Convert time_t to str, like '2012-12-21 23:59:59'
inline std::string TimeToStr(const time_t &tTime) {
  struct tm tmTime;
  TimeToTm(tTime, tmTime);
  return TmToStr(tmTime);
}

/// Convert str to time_t
inline time_t StrToTime(const std::string &strTime) {
  tm tmTime;
  if (StrToTm(strTime, tmTime))
    return TmToTime(tmTime);
  else
    return 0;
}

/// YYYYMMDDHHMMSS => timestamp
/// like convert '20121221235959' to time_t
static int GetTimeByY4MDHMS2(const std::string &date, time_t *p_time) {
  if (14 != date.size())
    return -1;
  struct tm tm_date;
  tm_date.tm_year = atoi(date.substr(0, 4).c_str()) - 1900;
  tm_date.tm_mon = atoi(date.substr(4, 2).c_str()) - 1;
  tm_date.tm_mday = atoi(date.substr(6, 2).c_str());
  tm_date.tm_hour = atoi(date.substr(8, 2).c_str());
  tm_date.tm_min = atoi(date.substr(10, 2).c_str());
  tm_date.tm_sec = atoi(date.substr(12, 2).c_str());
  tm_date.tm_isdst = 0;
  *p_time = mktime(&tm_date);
  return 0;
}

/// timestamp => YYYYMMDDHHMMSS
/// like convert time_t to '20121221235959'
static int GetY4MDHMS2(time_t t, std::string *p_datetime) {
  p_datetime->clear();

  char buf[20];
  struct tm tm_now;
  localtime_r(&t, &tm_now);

  snprintf(buf, sizeof(buf), "%.4d%.2d%.2d%.2d%.2d%.2d",
          tm_now.tm_year + 1900,
          tm_now.tm_mon + 1,
          tm_now.tm_mday,
          tm_now.tm_hour,
          tm_now.tm_min,
          tm_now.tm_sec);
  *p_datetime = buf;
  return 0;
}

/// timestamp => YYYYMMDD
/// like convert time_t to '20121221'
static int GetY4MD2(time_t t, std::string *p_datetime) {
  p_datetime->clear();

  char buf[9];
  struct tm tm_now;
  localtime_r(&t, &tm_now);

  snprintf(buf, sizeof(buf), "%.4d%.2d%.2d",
           tm_now.tm_year + 1900, tm_now.tm_mon + 1, tm_now.tm_mday);
  *p_datetime = buf;
  return 0;
}
} } }
#endif  ///< _GALAXY_CRAWLER_UTIL_TIME_TIME_H_
