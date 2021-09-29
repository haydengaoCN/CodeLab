#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
 public:
  int integerBreak(int n) {
    std::vector<int> ans(58, 0);
    ans[2] = 1;
    for (auto idx = 3; idx <= n; ++idx) {
      int half = idx / 2;
      int left = 1;
      while (left <= half) {
        ans[idx] = std::max(ans[idx], left * std::max(idx - left, ans[idx - left]));
        ++left;
      }
    }
    return ans[n];
  }
};

int main() {
 Solution sol;
 std::cout << sol.integerBreak(10) << std::endl;

 return 0;
}
