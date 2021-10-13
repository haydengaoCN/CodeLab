#include <vector>
#include <iostream>

using namespace std;
class Solution {
 public:
  vector<vector<int>> permute(const vector<int>& nums) {
    if (nums.empty()) return ans;
    std::vector<bool> is_visited(nums.size(), false);
    std::vector<int> tmp;
    backtrace(0, nums, is_visited, tmp);
    return ans;
  }

 private:
  std::vector<std::vector<int>> ans;
  void backtrace(int level, const std::vector<int>& nums, std::vector<bool>& is_visited, std::vector<int>& tmp) {
    if (level == nums.size()) {
      ans.emplace_back(tmp);
      return;
    }
    for (auto idx = 0; idx < nums.size(); ++idx) {
      if (is_visited[idx]) {
        continue;
      }
      is_visited[idx] = true;
      tmp.emplace_back(nums[idx]);
      backtrace(level + 1, nums, is_visited, tmp);
      tmp.pop_back();
      is_visited[idx] = false;
    }
  }
};

int main() {
  Solution sol;
  auto ans = sol.permute(std::vector<int>({1, 2, 3}));
  for (const auto& vec : ans) {
    for (const auto& val : vec) {
      std::cout << val << ",";
    }
    std::cout << std::endl;
  }
  return 0;
}
