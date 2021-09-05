#include <vector>
#include <algorithm>
#include <iostream>
struct comp {
  bool operator () (const std::pair<int, int>& left, const std::pair<int, int>& right) {  // low -> up
    return left.first < right.first;
  }
};
void PrintVec(const std::vector<std::pair<int, int> >& vec) {
  for (auto p : vec) {
    std::cout << p.first << "\t" << p.second << std::endl;
  }
}
int main() {
  std::vector<std::pair<int, int> > vec;
  vec.push_back(std::make_pair(1, 2));
  vec.push_back(std::make_pair(3, 4));
  vec.push_back(std::make_pair(5, 4));
  std::sort(vec.begin(), vec.end(), comp());
  PrintVec(vec);
  return 0;
}
