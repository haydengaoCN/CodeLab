#include <string>
#include <iostream>

class Solution {
 public:
  bool validPalindrome(std::string s) {
    return Check(s, 0, s.size() - 1);
  }
 
 private:
  bool Check(const std::string& s, int left, int right, bool is_first_warning = true) {
    std::cout << left << "," << right << std::endl;
    while (left <= right && s[left] == s[right]) {
      ++left;
      --right; 
    }
    std::cout << left << "," << right << std::endl;
    if (left > right) {
      return true;
    }
    if (!is_first_warning) {
      return false;
    }
    return Check(s, left + 1, right, false) || Check(s, left, right - 1, false);
  }
};

int main() {
  Solution sol;
  std::cout << sol.validPalindrome("aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga") << std::endl;
  std::cout << sol.validPalindrome("acbba") << std::endl;
  return 0;
}
