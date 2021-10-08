#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat) {
    const int N = mat.size();
    const int M = mat[0].size();
    std::vector<std::vector<int>> ans(N, std::vector<int>(M, INT_MAX - 1));
    for (int n = 0; n < N; ++n) {
      for (int m = 0; m < M; ++m) {
        if (mat[n][m] == 0) {
          ans[n][m] = 0;
          continue;
        }
        if (n > 0) {
          ans[n][m] = 1 + std::min(ans[n - 1][m], ans[n][m]);
        }
        if (m > 0) {
          ans[n][m] = 1 + std::min(ans[n][m - 1], ans[n][m]);
        }
      }
    }

    for (int n = N - 1; n >= 0; --n) {
      for (int m = M - 1; m >= 0; --m) {
        if (ans[n][m] == 0) {
          continue;
        }
        if (m > 0) {
          ans[n][m] = 1 + std::min(ans[n][m], ans[n][m - 1]);
        }
        if (n > 0) {
          ans[n][m] = 1 + std::min(ans[n][m], ans[n - 1][m]);
        }
      }
    }
    return ans;
  }
};

int main() {
  return 0;
}
