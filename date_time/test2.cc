#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
  time_t now, now1, now2;
  struct tm  ts;
  char       buf[80];

  // Get current time
  time(&now);
  ts = *localtime(&now);
  // strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
  strftime(buf, sizeof(buf), "%Y%m%d%H", &ts);
  printf("Local Time %s\n", buf);

  //UTC time
  now2 = now - 19800;  //from local time to UTC time
  ts = *localtime(&now2);
  strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
  printf("UTC time %s\n", buf);

  //TAI time valid upto next Leap second added
  now1 = now + 37;    //from local time to TAI time
  ts = *localtime(&now1);
  strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
  printf("TAI time %s\n", buf);

  return 0;
}
