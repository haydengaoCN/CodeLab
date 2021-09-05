#include <iostream>
#include <vector>
#include <string>

#include "wait_sync.h"

int main() {
  ParallelWriter excute_in_parallel(3);

  std::vector<std::string> tasks_to_be_done {
      "hello",
      "world"
  };
  
  for (const auto& task : tasks_to_be_done) {
    excute_in_parallel.create_work("hello");
    if (excute_in_parallel.wait_to_sync()) {
      std::cout << "task:" << task << " done." << std::endl;
    } else {
      std::cout << "failed to process task:" << task << std::endl;
    }
  }

  return 0;
}