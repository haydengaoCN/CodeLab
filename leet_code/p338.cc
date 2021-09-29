#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<int> countBits(int n) {
    std::vector<int> ans(n + 1, 0);
    if (n == 0) {
      return ans;
    }
    ans[0] = 0, ans[1] = 1;
    int cur_num = 2;
    int cur_low_base = 2;
    int cur_high_base = cur_low_base * 2;
    while (cur_num <= n) {
      ans[cur_num] = 1 + ans[cur_num - cur_low_base];
      ++cur_num;
      if (cur_num == cur_high_base) {
        cur_low_base = cur_high_base;
        cur_high_base *= 2;
      }
    }
    return ans;
  }
};

int main() {
  Solution sol;
  for (const auto& val : sol.countBits(9)) {
    std::cout << val << ",";
  }
  std::cout << std::endl;
  return 0;
}
