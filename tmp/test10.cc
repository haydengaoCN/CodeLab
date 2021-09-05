#include <ctime>
#include <iostream>
#include <string>

using namespace std;

inline std::string date_string() {
    time_t rawtime;
    std::time(&rawtime);
    struct tm *tinfo = std::localtime(&rawtime);
    char buffer[12];
    strftime(buffer, 12, "%F", tinfo);
    return std::string(buffer);
}

time_t Date2Timestamp(const std::string& s) {
  struct tm tmlol;
  strptime(s.c_str(), "%Y-%m-%d %H:%M:%S", &tmlol);
  return mktime(&tmlol);
}

int main() {
  std::cout << Date2Timestamp("2021-01-17 07:58:30") << std::endl;
  return 0;
}
