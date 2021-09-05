#include <vector>
#include <iostream>

inline bool Reverse(bool b) {
    return b ? false : true;
}

std::vector<std::vector<int>> ReadIn(int& n, int& k) {
  std::cin >> n >> k;
  std::vector<std::vector<int>> tmp(k);
  for (auto idx = 0; idx < k; ++idx) {
      int cur_size = 0;
      std::cin >> cur_size;
      tmp[idx].resize(cur_size + 1);
      for (auto idx2 = 0; idx2 <= cur_size; ++idx2) {
          std::cin >> tmp[idx][idx2];
      }
  }
  return tmp;
}

bool CanKellyWinIn2Heap(const std::vector<int>& vec1, const int idx1, const std::vector<int>& vec2, const int idx2, bool is_kelly_turn) {
    if (idx1 > vec1.size() || idx2 > vec2.size()) {
        return is_kelly_turn;
    }
    if (vec1[idx1] != vec2[idx2]) {
        return is_kelly_turn;
    }
    // 这轮两排堆 第一张牌相等
    return CanKellyWinIn2Heap(vec1, idx1 + 1, vec2, idx2 + 1, Reverse(is_kelly_turn));
}

int main() {
    int sample_count = 0;
    std::cin >> sample_count;
    while (sample_count != 0) {
        --sample_count;
        int n, k;
        auto vecs = ReadIn(n, k);
        
        if (k == 2*n) {
            std:cout << "Kelly" << std::endl;
        }
        if (k == 2) {
            if (CanKellyWinIn2Heap(vecs[0], 1, vecs[1], 1, true)) {
                std::cout << "Kelly" << std::end;
            } else {
                std::cout << "Nacho" << std::endl;
            }
        }
        std::cout << "Nacho" << std::endl;
    }
}
