#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
 public:
  int findRepeatNumber(std::vector<int>& nums) {
    int idx = 0;
    while (idx < nums.size()) {
      if (nums[idx] == idx) {
        ++idx;
	      continue;
      }
      if (nums[nums[idx]] == nums[idx]) {
        return nums[idx];
      }
      std::swap(nums[idx], nums[nums[idx]]);
    }
    return -1;
  }
};

int main() {
  std::vector<int> nums{0, 1, 1, 3, 4};
  Solution sol;
  std::cout << sol.findRepeatNumber(nums) << std::endl;

  return 0;
}
