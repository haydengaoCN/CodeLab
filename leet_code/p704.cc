#include <iostream>
#include <vector>

using namespace std;
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
      int mid = (right - left) / 2 + left;
      if (nums[mid] == target) {
        return mid;
	    }
	    if (nums[mid] < target) {
	      left = mid + 1;
	    } else {
	      right = mid;
	    }
	  }
	  return (nums[left] == target) ? left : -1;
  }
};

int main() {
  Solution sol;
  std::vector<int> nums{-1, 0, 3, 5, 9, 12};
  std::cout << sol.search(nums, 13) << std::endl;

  return 0;
}
