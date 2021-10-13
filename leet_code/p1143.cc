#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Solution {
 public:
  int longestCommonSubsequence(string text1, string text2) {
    int n1 = text1.size();
    int n2 = text2.size();
    std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1, 0));
    for (int i = 1; i <= n1; ++i) {
      for (int j = 1; j <= n2; ++j) {
        if (text1[i-1] == text2[j-1]) {
          dp[i][j] = dp[i-1][j-1] + 1;
        } else {
          dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
        }
      }
    }
    std::cout << dp[n1][n2] << "-" << revert(text1, text2, dp) << std::endl;
    return dp[n1][n2];
  }
 private:
  std::string revert(std::string& text1, std::string& text2, std::vector<std::vector<int>>& dp) {
    int i = text1.size(), j = text2.size();
    std::string ans;
    while (i >= 1 && j >= 1) {
      if (text1[i - 1] == text2[j - 1]) {
        ans += text1[i-1];
        --i;
        --j;
      } else {
        if (dp[i][j-1] == dp[i-1][j]) {
          --j;
        } else if (dp[i][j-1] > dp[i-1][j]) {
          --j; 
        } else {
          --i;
        }
      }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};

int main() {
  std::string str1 = "abcde";
  std::string str2 = "aaabcdeaaaa";
  Solution sol;
  sol.longestCommonSubsequence(str1, str2);
  return 0;
}
