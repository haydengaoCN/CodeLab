#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

class Solution {
 public:
  std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
    std::vector<int> ans;
    if (words.empty()) {
      return ans;
    }
    const int kWordLen = words[0].size();
    const int kWordNum = words.size();
    std::unordered_map<std::string, int> word_map;
    for (const auto& val : words) {
      auto counted = word_map[val];
      word_map[val] = counted + 1;
	  };
	  for (const auto &[word, count] : word_map) {
	    std::cout << word << "-" << count << std::endl;
	  }
	  std::cout << std::endl;

    for (auto idx = 0; idx < s.size() - kWordLen; ++idx) {
      std::unordered_map<std::string, int> cur_window_record;
      bool not_match = false;
      for (int count = 0, left = idx; count < kWordNum; ++count, left += kWordLen) {
        std::string cur_word = s.substr(left, kWordLen);
	      std::cout << cur_word;
		    if (word_map.count(cur_word) == 0) {  // not matched word
	        not_match = true;
		      std::cout << "break1" << std::endl;
		      break;
		    }
		    auto counted = cur_window_record[cur_word];
		    std::cout << counted << "-" << cur_window_record[cur_word] << std::endl;
	      if (counted + 1 > word_map[cur_word]) {
		      not_match = true;
		      std::cout << "break2" << std::endl;
		      break;
		    }
		    cur_window_record[cur_word] = counted + 1;
      }  // kWordNum
      std::cout << "cur_window_record:" << cur_window_record.size() << std::endl;
      if (!not_match && cur_window_record == word_map) {
        ans.emplace_back(idx);
	    }
    }  // s
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<std::string> words{"word","good","best","good"};
  auto ans = sol.findSubstring("wordwordgoodgoodgoodbestword", words);
  for_each(ans.begin(), ans.end(), [](const int& val) { std::cout << val << std::endl;});
  return 0;
}
