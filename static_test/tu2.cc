#include "tu2.h"

#include <iostream>

void foo_in_tu2() {
  std::cout << "in tu2: "
            << "global_static_variable:" << &global_static_variable
            << ", global_constexpr_variable:" << & global_constexpr_variable
            << ", kModuleVideoDeviceId:" << &kModuleVideoDeviceId
            << ", kModuleVideoDeviceId2:" << &kModuleVideoDeviceId2
            << std::endl;
}