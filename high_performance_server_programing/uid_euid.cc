#include <unistd.h>
#include <stdio.h>

int main () {
  uid_t uid = getuid();
  uid_t euid = geteuid();
  printf("user id:%d, effective userid:%d", uid, euid);
  return 0;
}
