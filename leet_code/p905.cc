#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
 public:
  vector<int> sortArrayByParity(vector<int>& nums) {
    int even_pos = -1;
    for (auto& val : nums) {
      if (val % 2 == 1) {
        continue;
      }
      std::swap(val, nums[++even_pos]);
    }
    return nums;
  }
};

int main() {
  Solution sol;
  std::vector<int> nums{3, 1, 2, 4, 7};
  for (const auto& val : sol.sortArrayByParity(nums)) {
    std::cout << val << ",";
  }
  std::cout << std::endl;
  return 0;
}
