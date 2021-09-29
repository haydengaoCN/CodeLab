#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() <= 1) {
      return 0;
    }
    std::sort( intervals.begin(), intervals.end(), [](const std::vector<int>& vec1, const std::vector<int>& vec2) { return vec1[0] < vec2[0];});
    int ans = 0;
    auto prev = 0;
    for (auto idx = 1; idx < intervals.size(); ++idx) {
      if (intervals[prev][1] <= intervals[idx][0]) {
        prev = idx;
        continue;
      }
      // overlapped
      ++ans;
      if (intervals[prev][1] > intervals[idx][1]) {
        prev = idx;
      }
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<int>> vecs{
    {1, 4}, {2, 3}, {1, 3}};

  std::cout << sol.eraseOverlapIntervals(vecs) << std::endl;

  return 0;
}
