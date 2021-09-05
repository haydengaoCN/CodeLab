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

// start a connection
int Connect(int argc, char* argv[]) {
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
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  assert(sock > 0);

  if (connect(sock, (struct sockaddr*)(&address), sizeof(address)) < 0) {
    printf("connection error.\n");
    return 1;
  } else {
    char buffer[1024];
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("%s", buffer);
    close(sock);
  }

  return 0;
}

}  // namespace SockerProgram

int main(int argc, char* argv[]) {
  return SocketProgram::Connect(argc, argv);
}