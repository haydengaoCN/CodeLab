//describe:for the time of touching-fish
//date:20210205
//author:haydengao

#include <stdio.h>
#include <unistd.h>  // for close(), read()
#include <sys/epoll.h>  // for epoll_create1, epoll_ctl, struct epoll_event
#include <string.h>  // for strncmp

/*
// see epoll.h
1. 区分epoll_fd和普通的fd
2. struct epoll_event
  struct epoll_event {
    uint32_t events;	/* Epoll events */
    epoll_data_t data;	/* User data variable *
  }
3. int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
  输出参数：
   @events: 捕捉到的fd存储在该参数上；
  输入参数：
   @timeout: 1) 0, then epoll_wait() shall return immediately, even if no events are available;
             2) -1, epoll_wait() shall block until either a requested event occurs or the call is interrupted;
             3) epoll_wait等待timeout(ms)后，返回；
   @maxevent: 最多能捕捉到的fd；毕竟events就这么大。
   @epfd    : 指定epoll_wait等待的地方。

*/

int main() {
  int epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    fprintf(stderr, "Failed to create epoll file descriptor\n");
    return 1;
  }

  const size_t kMaxEvent = 5;
  struct epoll_event event, events[kMaxEvent];
  event.events = EPOLLIN;
  event.data.fd = 0;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event)) {
    fprintf(stderr, "Failed to add file descriptor to epoll\n");
    close(epoll_fd);
    return 1;
  }

  const size_t kReadSize = 10;
  char read_buffer[kReadSize + 1];
  bool is_running = true;
  while (is_running) {
    printf("\nPolling for input...\n");
    size_t event_count = epoll_wait(epoll_fd, events, kMaxEvent, 3000/*timeout*/);
    printf("%d ready events\n", event_count);
    for (size_t idx = 0; idx < event_count; ++idx) {
      printf("Reading file descritor %d --", events[idx].data.fd);
      size_t bytes_read = read(events[idx].data.fd, read_buffer, kReadSize);
      printf("%zd bytes read.\n", bytes_read);
      read_buffer[bytes_read] = '\0';
      printf("Read %s\n", read_buffer);
      
      if (!strncmp(read_buffer, "stop\n", 5)) {
        is_running = false;
      }
    }
  } // end while

  if (close(epoll_fd)) {
    fprintf(stderr, "Failed to close epoll fd\n");
    return 1;
  }
  return 0;
}
