#include <string>
#include <iostream>

int main() {
  std::string ad_type = "WVL";
  if (ad_type == "WVL") {
		std::cout << "same!" << std::endl;
  }
  if (ad_type != "WVL" || ad_type != "WPB") {
		std::cout << "not same!" << std::endl;
  }
  return 0;
}
