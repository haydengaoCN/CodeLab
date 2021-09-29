#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::string minWindow(std::string s, std::string t) {
    std::vector<bool> chars_in_t(128, false);
    std::vector<int> char_counter(128, 0);
    for (const auto& ch : t) {
      chars_in_t[ch] = true;
      ++char_counter[ch];
    }
    int cnt = 0, left = 0, right = 0;
    int max_size = s.size() + 1;
    std::string ans;
    while (right < s.size()) {
      if (chars_in_t[s[right]]) {
        if (--char_counter[s[right]] >= 0) {
          ++cnt;
        }
        while (cnt == t.size()) {
          int cur_len = right - left + 1;
          if (cur_len < max_size) {
            max_size = cur_len;
            ans = s.substr(left, cur_len);
          }
          if (chars_in_t[s[left]]) {
            if (++char_counter[s[left]] > 0) {
              --cnt;
            }
          }
          ++left;
        }
      }
      ++right;
    }
    return ans;
  }
};

int main() {
  // std::string s = "ADOBECODEBANC";
  std::string s = "BANC";
  std::string t = "ABC";
  Solution sol;
  std::cout << sol.minWindow(s, t) << std::endl;
  return 0;
}
