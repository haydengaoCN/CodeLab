#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
class Solution {
 public:
  std::string longestPalindrome(std::string s) {
    if (s.empty()) return 0;
    int max_len = 1, begin = 0;
    for (auto idx = 0; idx < s.size(); ++idx) {
      int len1 = extend(s, idx, idx + 1);
      int len2 = extend(s, idx, idx);
      if (len1 > len2 && len1 > max_len) {
        begin = idx - len1 / 2 + 1;
        max_len = len1;
      } else if (len2 > len1 && len2 > max_len) {
        begin = idx - (len2 + 1) / 2 + 1; 
        max_len = len2;
      }
    }
    return s.substr(begin, max_len);
  }
 private:
  int max3(int v1, int v2, int v3) {
    return std::max(v1, std::max(v2, v3));
  }

  int extend(const std::string& s, int left, int right) {
    int len = (right == left) ? -1 : 0;
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
      --left;
      ++right;
      len += 2;
    }
    return len;
  }
};

int main() {
  Solution sol;
  std::cout << sol.longestPalindrome("babdb") << std::endl;
  return 0;
}
