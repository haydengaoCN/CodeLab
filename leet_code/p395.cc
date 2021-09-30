#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;
class Solution {
 public:
    int longestSubstring(string s, int k) {
      std::vector<int> char_counter(128 ,0);
      auto tot_unique_chars = 0;
      for (const auto& ch : s) {
        if (char_counter[ch] == 0) {
          ++tot_unique_chars;
        }
        ++char_counter[ch];
      }
      int ans = 0;
      for (auto target_unique_num = 1; target_unique_num <= tot_unique_chars; ++target_unique_num) {
        std::vector<int> counter(128, 0);
        int left = 0, right = 0, unique_chars = 0;
        int chars_over_k = 0;
        while (right < s.size()) {
          std::cout << left << "," << right << ",";
          if (unique_chars <= target_unique_num) {
            if (counter[s[right]] == 0) ++unique_chars;
            ++counter[s[right]];
            if (counter[s[right]] == k) ++chars_over_k;
            ++right;
          } else {
            if (counter[s[left]] == k) --chars_over_k;
            --counter[s[left]];
            if (counter[s[left]] == 0) --unique_chars;
            ++left;
          }
          if (unique_chars == target_unique_num && chars_over_k == target_unique_num) {
            ans = std::max(ans, right - left);
          }
          std::cout << unique_chars << std::endl;
        }
      }
      return ans;
    }
    int Sol1(string s, int k) {
        int countMap[26];
        int maxUnique = getMaxUniqueLetters(s);
        int result = 0;
        for (int currUnique = 1; currUnique <= maxUnique; currUnique++) {
            // reset countMap
            memset(countMap, 0, sizeof(countMap));
            int windowStart = 0, windowEnd = 0, idx = 0, unique = 0, countAtLeastK = 0;
            while (windowEnd < s.size()) {
                // expand the sliding window
                if (unique <= currUnique) {
                    idx = s[windowEnd] - 'a';
                    if (countMap[idx] == 0) unique++;
                    countMap[idx]++;
                    if (countMap[idx] == k) countAtLeastK++;
                    windowEnd++;
                }
                // shrink the sliding window
                else {
                    idx = s[windowStart] - 'a';
                    if (countMap[idx] == k) countAtLeastK--;
                    countMap[idx]--;
                    if (countMap[idx] == 0) unique--;
                    windowStart++;
                }
                if (unique == currUnique && unique == countAtLeastK)
                    result = max(windowEnd - windowStart, result);
            }
        }

        return result;
    }

    // get the maximum number of unique letters in the string s
    int getMaxUniqueLetters(string s) {
        bool map[26] = {0};
        int maxUnique = 0;
        for (int i = 0; i < s.length(); i++) {
            if (!map[s[i] - 'a']) {
                maxUnique++;
                map[s[i] - 'a'] = true;
            }
        }
        return maxUnique;
    }
};

int main() {
  Solution sol;
  // std::cout << sol.longestSubstring("eababcb", 2) << std::endl;
  // std::cout << sol.longestSubstring("aaabb", 3) << std::endl;
  // std::cout << sol.longestSubstring("aaaaaaaaaaaabcdefghijklmnopqrstuvwzyz", 3) << std::endl;
  std::cout << sol.longestSubstring("abcd", 1) << std::endl;
}
