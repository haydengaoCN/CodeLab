#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
 public:
  int findMinArrowShots(vector<vector<int>>& points) {
    return Sol3(points);
  }

 private:
  int Sol3(std::vector<std::vector<int>>& points) {
    std::sort(points.begin(), points.end(), [](const std::vector<int>& vec1, const std::vector<int>& vec2) { return vec1[0] < vec2[0];});
    int ans = 0;
    int idx = points.size() - 1;
    while (idx >= 0) {
      int arrow = points[idx][0];
      while (idx > 0&& points[idx - 1][1] >= arrow) {
        --idx;
      }
      ++ans;
      --idx;
    }
    return ans;
  }

  int Sol2(std::vector<std::vector<int>>& points) {
    std::sort(points.begin(), points.end(), [](const std::vector<int>& vec1, const std::vector<int>& vec2) { return vec1[0] < vec2[0];});
    int ans = 0;
    int idx = 0;
    while (idx < points.size()) {
      int arrow = points[idx][1];
      while (idx < points.size() - 1 && points[idx + 1][0] <= arrow) {
        ++idx;
        arrow = std::min(arrow, points[idx][1]);
      }
      ++ans;
      ++idx;
    }
    return ans;
  }

  int Sol1(vector<vector<int>>& points) {
    if (points.size() <= 1) {
      return points.size();
    }
    std::sort(points.begin(), points.end(), [](const std::vector<int>& vec1, const std::vector<int>& vec2) { return vec1[0] < vec2[0]; });
    std::vector<int> prev_overlapped_inter = points[0];
    int ans = 1;
    for (auto idx = 1; idx < points.size(); ++idx) {
      auto cur_overlapped_inter = GetOverlapped(points[idx - 1], points[idx]);
      auto cross_inter = GetOverlapped(prev_overlapped_inter, cur_overlapped_inter);
      if (cross_inter.empty()) {
        ++ans;
        prev_overlapped_inter = points[idx];
      } else {
        prev_overlapped_inter = cross_inter;
      }
    }
    return ans;
  }
  
  std::vector<int> GetOverlapped(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> cross_inter;
    if (v1.empty() || v2.empty()) {
      return cross_inter;
    }
    if (v2[0] > v1[1]) {
      return cross_inter;
    }
    cross_inter.emplace_back(v2[0]);
    cross_inter.emplace_back(std::min(v1[1], v2[1]));
    return cross_inter;
  }

  void Show(const std::vector<int>& vec) {
    for_each(vec.begin(), vec.end(), [](const int& val) { std::cout << val << ",";});
    std::cout << std::endl;
  }
};

int  main() {
  Solution sol;
  std::vector<std::vector<int>> vecs {
    {1, 2}, {3, 4}, {5, 6}, {7, 8}
  };
  std::cout << sol.findMinArrowShots(vecs) << std::endl;
  return 0;
}
