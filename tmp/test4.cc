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
        return Reverse(is_kelly_turn);
    }
    if (vec1[idx1] != vec2[idx2]) {
        return Reverse(is_kelly_turn);
    }
    // 这轮两排堆 第一张牌相等
    return CanKellyWinIn2Heap(vec1, idx1 + 1, vec2, idx2 + 1, Reverse(is_kelly_turn));
}

bool CanKellyWin(std::vector<std::vector<int>*> vecs, std::vector<int> index, bool is_kelly_turn) {
    std::vector< std::vector<int>* > valid_vecs;
    std::vector< int > valid_index;
    for (auto idx = 0; idx < index.size(); ++idx) {
        if (index[idx] < vecs[idx]->size()) {
            valid_vecs.emplace_back(vecs[idx]);
            valid_index.emplace_back(index[idx]);
        }
    }
    if (valid_vecs.size() == 2) {
        return CanKellyWinIn2Heap(*valid_vecs[0], index[0], *valid_vecs[1], index[1], is_kelly_turn);
    }
    for (auto idx1 = 0; idx1 < valid_vecs.size() - 1; ++idx1) {
        for (auto idx2 = idx1 + 1; idx2 < valid_vecs.size(); ++idx2) {
            if (valid_vecs[idx1]->at(valid_index[idx1]) == valid_vecs[idx2]->at(valid_index[idx2])) {
                ++valid_index[idx1];
                ++valid_index[idx2];
                if (CanKellyWin(valid_vecs, valid_index, Reverse(is_kelly_turn))) {
                    return true;
                }
                --valid_index[idx1];
                --valid_index[idx2];
            }
        }
    }
    return false;
}

int main() {
    int sample_count = 0;
    std::cin >> sample_count;
    while (sample_count != 0) {
        --sample_count;
        int n, k;
        auto vecs = ReadIn(n, k);
        
        if (k == 2*n) {
            std::cout << "Kelly" << std::endl;
            continue;
        }
        if (k == 2) {
            if (CanKellyWinIn2Heap(vecs[0], 1, vecs[1], 1, true)) {
                std::cout << "Kelly" << std::endl;
            } else {
                std::cout << "Nacho" << std::endl;
            }
            continue;
        }
        std::vector<std::vector<int>*> valid_vec;
        std::vector<int> valid_index;
        for (auto&& vec : vecs) {
            valid_vec.emplace_back(&vec);
            valid_index.emplace_back(1);
        }
        if (CanKellyWin(valid_vec, valid_index, true)) {
            std::cout << "Kelly" << std::endl;
        } else {
            std::cout << "Nacho" << std::endl;
        }

    }
    return 0;
}
