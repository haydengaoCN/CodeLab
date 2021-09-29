#include <iostream>
#include <cmath>

class Solution {
 public:
  bool judgeSquareSum(int c) {
    uint64_t left = 0, right = c;  // std::sqrt(c);
    uint64_t ans = c;
    while (left <= right) {
      uint64_t tmp = left * left;
      tmp += right * right;
      std::cout << left << "," << right << "," << tmp << std::endl;
      if (tmp == ans) {
        return true;
      }
      if (tmp < ans) {
        ++left;
      } else {
        --right;
      }
    }
    return false;
  }
};

int main() {
  Solution sol;
  sol.judgeSquareSum(100000);
  return 0;
}
