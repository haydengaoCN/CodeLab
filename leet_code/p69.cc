#include <iostream>

class Solution {
 public:
  int mySqrt(int x) {
    int left = 0, right = x;
    while (left < right) {
      int mid = (right - left) / 2 + left;
      int sqrt = mid * mid;
      if (sqrt == x) {
        return mid;
      }
      if (sqrt < x) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left * left <= x ? left : left - 1;
  }
};

int main() {
  Solution sol;
  std::cout << sol.mySqrt(16) << std::endl;
  return 0;
}
