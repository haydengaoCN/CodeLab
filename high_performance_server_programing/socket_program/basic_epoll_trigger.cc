/*
* author:haydengao
* description: epoll trigger methods : LT vs. ET
* date:20210824
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

namespace SocketProgram {

// 非阻塞socket
// ET边缘触发要求non-blocking socket
int SetNonBlocking(int fd) {
  int old_option = fcntl(fd, F_GETFL);
  int new_option = old_option | O_NONBLOCK;
  fcntl(fd, F_SETFL, new_option);
  return old_option;
}
// epoll 监听fd
void AddEpollFD(int epoll_fd, int fd, bool enable_et) {
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN;
  if (enable_et) {
    event.events |= EPOLLET;
  }
  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
}
// Level Trigger
void LT(epoll_event* events, int number, int epoll_fd, int listen_fd) {
  char buff[BUFFER_SIZE];
  for (auto idx = 0; idx < number; ++idx) {
    int sockfd = events[idx].data.fd;
    if (sockfd == listen_fd) {
      struct sockaddr_in client_addr;
      socklen_t client_addr_len = sizeof(client_addr);
      int connfd = accept(listen_fd, (struct sockaddr*)(&client_addr), &client_addr_len);
      AddEpollFD(epoll_fd, connfd, false);
      printf("New connection established:%d\n", connfd);
    } else if (events[idx].events & EPOLLIN) {
      printf("event trigger once\n");
      memset(buff, '\0', BUFFER_SIZE);
      auto ret = recv(sockfd, buff, BUFFER_SIZE - 1, 0);
      if (ret <= 0) {
        printf("recv error:%d\n", errno); 
        close(sockfd);
        continue;
      }
      printf("get %d bytes of content:%s\n", ret, buff);
    } else {
      printf("unknown case.\n");
    }
  }
}
// Edge Trigger
void ET(epoll_event* events, int number, int epoll_fd, int listen_fd) {
  char buff[BUFFER_SIZE];
  for (auto idx = 0; idx < number; ++idx) {
    int sockfd = events[idx].data.fd;
    if (sockfd == listen_fd) {
      struct sockaddr_in client_addr;
      socklen_t client_addr_len = sizeof(client_addr);
      int connfd = accept(listen_fd, (struct sockaddr*)(&client_addr), &client_addr_len);
      AddEpollFD(epoll_fd, connfd, true);
      printf("New connection established:%d\n", connfd);
    } else if (events[idx].events & EPOLLIN) {
      printf("event trigger once\n");
      while (1) {
        memset(buff, '\0', BUFFER_SIZE);
        auto ret = recv(sockfd, buff, BUFFER_SIZE - 1, 0);        
        if (ret < 0) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) {
            // 对于非阻塞IO，这个if条件表示数据已经完全读取
            printf("read later\n");
            break;
          } else {
            printf("error %d occurs when recv.\n", errno);
            close(sockfd);
            break;
          }
        } else if (ret == 0) {
          close(sockfd);
        } else {
          printf("get %d bytes of content:%s\n", ret, buff);
        }
      }  // end while
    } else {
      printf("unknown case.\n");
    }
  }
}

}  // namespace SocketProgram

int main(int argc, char* argv[]) {
    if (argc < 2) {
    printf("ip and port are required.\n");
    return 1;
  }
  const char* ip = argv[1];
  int port = atoi(argv[2]);

  auto address = [&ip, port]() {
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    // 将IP地址从文本转化为二进制格式
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    return address;
  }();

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd <= 0) {
    printf("create socket error:%d\n", errno);
    return 1;
  }

  // socket命名
  if (bind(sockfd, (struct sockaddr*)(&address), sizeof(address)) == -1) {
    printf("bind error:%d\n", errno);
    return 1;
  }

  if (listen(sockfd, 5) == -1) {
    printf("listen error:%d", errno);
    return 1;
  }

  epoll_event events[ MAX_EVENT_NUMBER ];
  int epollfd = epoll_create(5);
  assert( epollfd != -1 );
  SocketProgram::AddEpollFD(epollfd, sockfd, true);
  while (1) {   
    int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
    if (ret < 0) {
      printf( "epoll failure\n" );
      break;
    }
    // SocketProgram::LT(events, ret, epollfd, sockfd);
    SocketProgram::ET(events, ret, epollfd, sockfd);
  }   

  close(sockfd);
  return 0;
}