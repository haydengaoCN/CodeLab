#include <iostream>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    std::vector<int> ans{-1, -1};
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
      int mid = (right - left) / 2 + left;
      if (nums[mid] == target) {
        std::cout << left << "," << right << "," << mid << std::endl;
        int l = left, r = mid;
        while (l < r) {
          int mid = (r - l) / 2 + l;
          if (nums[mid] == target) {
            r = mid;
          } else {
            l = mid + 1;      
          }
        }
        std::cout << l << "," << r << std::endl;
        ans[0] = l;
        l = mid, r = right;
        while (l < r) {
          int mid = (r + 1 - l) / 2 + l;
          if (nums[mid] == target) {
            left = mid;
          } else {
            r = mid - 1;
          }
        }
        std::cout << l << "," << r << std::endl;
        ans[1] = l;
        return ans;
      }
      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<int> nums{5, 7, 7, 8, 8, 10};
  auto ans = sol.searchRange(nums, 7);
  std::cout << ans[0] << "," << ans[1] << std::endl;
  return 0;
}
