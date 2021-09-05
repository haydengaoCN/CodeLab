#include <vector>
#include <iostream>

class Solution {
 public:
  int findMin(std::vector<int>& nums) {
    if (nums.back() >= nums[0]) {  // assert(!empty)
      return nums[0];
    }
    int left = 0, right = nums.size() - 1;
    while (left < right) {
      int mid = (right - left) / 2 + left;
      if (nums[mid] >= nums[0]) {  // first half
        left = mid + 1;
      } else {  // second half
        if (nums[mid] < nums[mid - 1]) {
	        return nums[mid];
	      }
	      right = mid;
      }
    }
    return nums[left];  // must be found in loop.
  }
};
