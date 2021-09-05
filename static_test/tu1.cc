#include "tu1.h"

#include <iostream>

void foo_in_tu1() {
  std::cout << "in tu1: "
            << "global_static_variable:" << &global_static_variable
            << ", global_constexpr_variable:" << & global_constexpr_variable
            << ", kModuleVideoDeviceId:" << &kModuleVideoDeviceId
            << ", kModuleVideoDeviceId2:" << &kModuleVideoDeviceId2
            << std::endl;
}

