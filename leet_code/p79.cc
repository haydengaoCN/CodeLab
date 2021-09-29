#include <vector>
#include <string>
#include <iostream>

class Solution {
 public:
   bool exist(std::vector<std::vector<char>>& board, std::string word) {
     if (board.empty()) {
       return word.empty();
     }
     if (word.empty()) {
       return true;
     }
     // board[m][n]
     N = board[0].size();
     M = board.size();
     is_used.resize(M);
     for (auto& vec : is_used) {
       vec.resize(N, false);
     }
     for (auto m = 0; m < M; ++m) {
       for (auto n = 0; n < N; ++n) {
         if (FindNextChar(board, m, n, word, 0)) {
           return true;
         }
       }
     }
     return false;
   }
 
 private:
  bool FindNextChar(const std::vector<std::vector<char>>& board, int cur_pos_m, int cur_pos_n, const std::string& word, int cur_pos) {
    std::cout << cur_pos << std::endl;
    if (cur_pos == word.size()) {
      return true;
    }

    if (!isLegal(cur_pos_m, cur_pos_n)) {
      return false;
    }


    if (is_used[cur_pos_m][cur_pos_n] || board[cur_pos_m][cur_pos_n] != word[cur_pos]) {
      return false;
    }
    
    is_used[cur_pos_m][cur_pos_n] = true;
    bool ret = FindNextChar(board, cur_pos_m + 1, cur_pos_n, word, cur_pos + 1) ||
               FindNextChar(board, cur_pos_m - 1, cur_pos_n, word, cur_pos + 1) ||
               FindNextChar(board, cur_pos_m, cur_pos_n + 1, word, cur_pos + 1) ||
               FindNextChar(board, cur_pos_m, cur_pos_n - 1, word, cur_pos + 1);
    if (!ret) {
      is_used[cur_pos_m][cur_pos_n] = false;
    }
    return ret;
  }

  bool isLegal(const int cur_pos_n, const int cur_pos_m) {
    return cur_pos_n >= 0 && cur_pos_n < N && cur_pos_m >= 0 && cur_pos_m < M; 
  }

  int N = 0;
  int M = 0;
  std::vector<std::vector<bool>> is_used;
};

int main() {
  Solution sol;
  std::vector<std::vector<char>> board {
      {'a', 'b', 'c', 'e'},
      {'s', 'f', 'c', 's'},
      {'a', 'd', 'e', 'e'}
  };
  std::cout << sol.exist(board, "abcced") << std::endl;

  return 0;

}


