#include <iostream>
#include <vector>

class Solution {
 public:
  bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    // n * m
    // matrix[M][N]
    const int M = matrix.size();
    const int N = matrix[0].size();
    
    int m = 0, n = N - 1;
    while ( m < M && n > 0) {
      int cur_val = matrix[m][n];
      if (cur_val == target) {
        return true;
      }
      if (cur_val > target) {
        n -= 1;
      } else {
        m += 1;
      }
    }
    return false;
  }
};

int main() {
  return 0;
}
