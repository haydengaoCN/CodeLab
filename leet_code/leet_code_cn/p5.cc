#include <string>
#include <iostream>

class Solution {
 public:
  std::string replaceSpace(std::string s) {
    int len = s.size();
    int space_count = 0;
    for_each(s.begin(), s.end(), [&space_count](const char& ch) {
        if (ch == ' ') ++space_count;});
    int final_len = len + space_count * ( 3 - 1);
    s.resize(final_len);

    // copy from back
    int reverse_idx = len - 1;
    int write_in_idx = final_len - 1;
    while (reverse_idx != write_in_idx) {
      if (s[reverse_idx] != ' ') {
        s[write_in_idx--] = s[reverse_idx--];
      } else {
        s[write_in_idx--] = '0';
        s[write_in_idx--] = '2';
        s[write_in_idx--] = '%';
        --reverse_idx;
      }
    }
    return s;
  }
};

int main() {
  Solution sol;
  std::cout << sol.replaceSpace("123 4") << std::endl;
  return 0;
}
