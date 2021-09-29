#include <iostream>
#include <vector>

using namespace std;
class Solution {
 public:
  bool checkPossibility(vector<int>& nums) {
    bool is_first_error = true;
    int idx = 0;
    while (idx < nums.size() - 1) {
      while (idx < nums.size() - 1 && nums[idx] <= nums[idx + 1]) {
        ++idx;
      }
      if (idx == nums.size() - 1) {
        return true;
      }
      // met bad case
      if (!is_first_error) {
        return false;
      }
      is_first_error = false;
      if (idx != 0 && nums[idx + 1] < nums[idx - 1]) {
        return false;
      }
      ++idx;
    }
    return true;
  }
};

int main() {
}
