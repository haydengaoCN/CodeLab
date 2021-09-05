#include <string>
#include <iostream>

#define INTRADELIM '_'

std::string SerializeAsString(std::string media_id_, int media_type_, int retry_time_ = 0) {
  auto ret = media_id_;
  ret.append(1, INTRADELIM);
  ret = ret + std::to_string(media_type_);
  ret.append(1, INTRADELIM);
  return std::move(ret) + std::to_string(retry_time_);
}

int main() {
  std::cout << SerializeAsString("abc", 1);
  return 0;
}
