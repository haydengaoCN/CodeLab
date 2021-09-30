#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
 public:
  string findLongestWord(string s, vector<string>& dictionary) {
    if (s.empty() || dictionary.empty() ) {
      return "";
    }
    std::sort(dictionary.begin(), dictionary.end(),
        [](const auto& str1, const auto& str2) {
        return str1.size() == str2.size() ? str1 < str2 : str1.size() > str2.size();});
    for (const auto& str : dictionary) {
      int idx = 0;
      bool find_all = true;
      for (const auto& ch : str) {
        while (idx < s.size() && s[idx] != ch) {
          ++idx;
        }
        if (idx == s.size()) {
          find_all = false;
          break;
        }
        ++idx;
      }
      if (find_all) {
        return str;
      }
     }
    return "";
  }
};

int main() {
  Solution sol;
  std::vector<std::string> dict{"ale","apple","monkey","plea", "abpcplaaa","abpcllllll","abccclllpppeeaaaa"};
  std::cout << sol.findLongestWord("abpcplea", dict) << std::endl;
  // std::vector<std::string> dict{"apple","ewaf","awefawfwaf","awef","awefe","ewafeffewafewf"};
  // std::cout << sol.findLongestWord("aewfafwafjlwajflwajflwafj", dict) << std::endl;
  return 0;
}

