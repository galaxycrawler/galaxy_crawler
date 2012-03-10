#include <stdio.h>
#include "../time.h"

using namespace galaxy_crawler::util::time;

int main() {
  uint64_t rdtsc_value = rdtsc();
  printf("rdtsc() (usec): %llu\n", rdtsc_value);

  uint64_t cur_time_us = GetCurTimeUs();
  printf("GetCurTimeUs() (usec): %llu\n", cur_time_us);

  uint32_t cur_time_ms = GetCurTimeMs();
  printf("GetCurTimeMs() (ms):   %lu\n", cur_time_ms);

  uint64_t cur_time_ms_arg = 0;
  GetCurTimeMs(&cur_time_ms_arg);
  printf("GetCurTimeMs(uint64_t *ms) (ms): %llu\n", cur_time_ms_arg);

  time_t rawtime;
  time(&rawtime);
  time_t hour_time = GetHourTime(rawtime, 19);
  printf("GetHourTime(rawtime, 19) (time_t): %llu\n", hour_time);

  struct tm tm_time;
  localtime_r(&rawtime, &tm_time);
  std::string now_time = TmToStr(tm_time);
  printf("TmToStr() (str): %s\n", now_time.c_str());

  struct tm world_end_time_tm;
  std::string world_end_time_str = "2011-02-28 23:59:59";
  bool is_succ = StrToTm(world_end_time_str, world_end_time_tm);
  printf("StrToTm() '%s' to '%d-%d-%d %d:%d:%d', is_succ = %s\n",
         world_end_time_str.c_str(),
         world_end_time_tm.tm_year,
         world_end_time_tm.tm_mon,
         world_end_time_tm.tm_mday,
         world_end_time_tm.tm_hour,
         world_end_time_tm.tm_min,
         world_end_time_tm.tm_sec,
         is_succ == true ? "true" : "false");
}

