#include <iostream>
#include <string>
#include <time.h>

void test1() {
  time_t cur_time = time(nullptr);
  tm basic_time_struct_;
  localtime_r(&cur_time, &basic_time_struct_);
  char date[15] = {'\0'};
  sprintf(date, "%04d%02d%02d%02d%02d%02d",
      basic_time_struct_.tm_year + 1900,
      basic_time_struct_.tm_mon + 1,
      basic_time_struct_.tm_mday,
      basic_time_struct_.tm_hour,
      basic_time_struct_.tm_min,
      basic_time_struct_.tm_sec);
  std::cout << date << std::endl;

}

int main() {
  test1();
  return 0;
}

