#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
class Solution {
 public:
  int candy(vector<int>& ratings) {
    if (ratings.empty()) {
      return 0;
    }
    std::vector<int> candies(ratings.size(), 1);
    // left -> right
    for (int idx = 1; idx < ratings.size(); ++idx) {
      if (ratings[idx] > ratings[idx - 1]) {
        ++candies[idx];
      }
    }
    // right -> left
    for (int idx = ratings.size() - 2; idx >= 0; --idx) {
      if (ratings[idx] > ratings[idx + 1] && candies[idx] <= candies[idx + 1]) {
        candies[idx] = candies[idx + 1] + 1;
      }
    }
    return std::accumulate(candies.begin(), candies.end(), 0);
  }
};

int main() {
  Solution sol;
  std::vector<int> ratings{1, 0 ,2};
  std::cout << sol.candy(ratings) << std::endl;

  return 0;
}

