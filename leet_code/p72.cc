#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
class Solution {
 public:
  int minDistance(string word1, string word2) {
    int n1 = word1.size();
    int n2 = word2.size();
    std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1, 0));
    for (int idx2 = 1; idx2 <= n2; ++idx2) {
      dp[0][idx2] = 1 + dp[0][idx2 - 1];
    }
    for (int idx1 = 1; idx1 <= n1; ++idx1) {
      dp[idx1][0] = 1 + dp[idx1 - 1][0];
    }
    for (int idx1 = 1; idx1 <= n1; ++idx1) {
      for (int idx2 = 1; idx2 <= n2; ++idx2) {
        if (word1[idx1 - 1] == word2[idx2 - 1]) {
          dp[idx1][idx2] = dp[idx1-1][idx2 - 1];
        } else {
          dp[idx1][idx2] = 1 + min3(
              dp[idx1 - 1][idx2],
              dp[idx1 - 1][idx2 - 1],
              dp[idx1][idx2 - 1]);
        }
      }
    }
    return dp[n1][n2];
  }

 private:
  int min3(const int v1, const int v2, const int v3) {
    return std::min(v1, std::min(v2, v3));
  }
};

int main() {
  return 0;
}
