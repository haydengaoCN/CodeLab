#include <vector>
#include <algorithm>

class Solution {
 public:
  int trap(std::vector<int>& height) {
    if (height.size() <= 2) return 0;
    int left_max = height[0];
    int right_max = height.back();
    int left = 1, right = height.size() - 2;
    int ans = 0;
    while (left <= right) {
      left_max = std::max(left_max, height[left]);
      right_max = std::max(right_max, height[right]);
      if (left_max < right_max) {
        int tmp = left_max - height[left];
        ans += tmp;
        ++left;
      } else {
        int tmp = right_max - height[right];
        ans += tmp;
        --right;
      }
    }
    return ans;
  }
};

int main() {
  return 0;
}
