#include <iostream>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <chrono>

std::condition_variable cv;
std::mutex cv_m;
int cur_goal = 0;
char nums_to_print = 3;

void printer(char ch) {
  const int target = ch - 'A';
  for (auto idx = 0; idx < nums_to_print; ++idx) {
    std::unique_lock<std::mutex> lc(cv_m);
    cv.wait(lc, [target] (){
        if (target != cur_goal) {
          std::cout << "target-pred:" << target << ":false" << std::endl;
        } else {
          std::cout << "target-pred:" << target << ":true" << std::endl;
        }
        return target == cur_goal; });
    std::cout << "target:" << target << "," << "cur_goal:" << cur_goal << ",";
    cur_goal = (cur_goal + 1) % 3;
    std::cout << "change cur_goal to:" << cur_goal << std::endl;
    // cv.notify_all();
  }
}

int main() {
  std::thread p1(printer, 'A'), p2(printer, 'B'), p3(printer, 'C');
  p1.join();
  p2.join();
  p3.join();
  return 0;
}
