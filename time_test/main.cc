#include <vector>
#include <string>
#include <stdio.h>
#include <time.h>
#include <iostream>

bool print(const std::vector< std::string >& input) {
  for (auto str : input) {
    std::cout << str << std::endl;
  }
  return true;
}

int main() {
  size_t preload_days_ = 2;
  std::vector< std::string > input;
  input.reserve(preload_days_);
  for (uint32_t i = 0; i < preload_days_; ++i) { // 遍历所有预加载天数
    // 日期格式yyyy-mm-dd
    time_t cur_time;
    tm local_time = { 0 };
    char timestr[64];
    time(&cur_time);
    cur_time += i * 86400;  // delay same day(s).
    localtime_r(&cur_time, &local_time);
    snprintf(timestr, sizeof(timestr), "%04d-%02d-%02d", local_time.tm_year + 1900,
             local_time.tm_mon + 1, local_time.tm_mday);
    input.emplace_back(std::string(timestr));
  }
  print(input);
  return 0;
}

