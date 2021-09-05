#include <iostream>
#include <vector>

class Solution {
 public:
  int search(std::vector<int>& nums, int target) {
    if (nums.empty()) {
      return -1;
    }
    bool is_in_first_half = (target >= nums[0]);
    int left = 0, right = nums.size() - 1;
    while (left < right) {
      int mid = (right - left) /2 + left;
      if (nums[mid] == target) {
        return mid;
	    }
	    if (nums[mid] >= nums[0]) {  // first half
	      if (is_in_first_half) {
	        if (nums[mid] > target) {
		        right = mid;
		      } else {
		        left = mid + 1;
		      }
	      } else {
	        left = mid + 1;
	      }
	    } else {  // second half
	      if (is_in_first_half) {
	        right = mid;
	      } else {
	        if (nums[mid] > target) {
		        right = mid;
			    } else {
			      left = mid + 1;
			    }
	      }
	    }
	  }  // while
	  return nums[left] == target ? left : -1;
  }
};

int main() {
  Solution sol;
  std::vector<int> nums{5, 8, 1, 2, 4};
  std::cout << "ans:" << sol.search(nums, 8) << std::endl;

  return 0;
}
