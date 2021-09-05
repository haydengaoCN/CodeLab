/*
* author:haydengao
* description: basic socket program pattern
* date:20210823
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

namespace SocketProgram {

// wait && recv one connection && quit
int RecvOnce(int argc, char* argv[]) {
  if (argc < 2) {
    printf("ip and port are required.\n");
    return 1;
  }
  const char* ip = argv[1];
  int port = atoi(argv[2]);

  // 初始化sock addr
  // 指定IP地址和端口，注意转化为网络序
  auto address = [&ip, port]() {
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    // 将IP地址从文本转化为二进制格式
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    return address;
  }();

  // PF_INET -> ipv4; PF_UNIX -> unix本地域协议族
  // SOCK_STREAM -> 流服务; SOCK_UGRAM -> 数据报
  // 0 -> 由前两个参数确定，设置为0表示使用默认协议
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

  // socket监听
  // backlog 参数提示内核监听队列的最大长度，超过这个长度将不再受理新的连接，客户端收到ECONNREFUSE
  // 典型值为5
  if (listen(sockfd, 5) == -1) {
    printf("listen error:%d", errno);
    return 1;
  }

  // accept once and then quit
  do {
    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    // 阻塞直到收到连接
    int connfd = accept(sockfd, (struct sockaddr*)(&client), &client_addrlength);
    if (connfd < 0) {
      printf("accept error:%d\n", errno);
    } else {
      char remote[INET_ADDRSTRLEN];
      char buffer[1024] = "Do not answer!!!\r\nDo not answer!!!\r\nDo not answer!!!\r\n\0";
      printf("connected with ip:%s and port:%d\n",
             inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN), ntohs(client.sin_port));
      send(connfd, buffer, strlen(buffer), 0);
      close(connfd);
    }
  } while(false);

  close(sockfd);
  return 0;
}
   
}  // namespace SocketProgram

int main(int argc, char* argv[]) {
  return SocketProgram::RecvOnce(argc, argv);
}
