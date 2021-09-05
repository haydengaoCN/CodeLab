#include <iostream>
#include <vector>

void WhoWin(const std::vector<int>& array, int win_count) {
  int winner = array[0], count = 1;
  int length = array.size();
  for (auto idx = 1; idx < length * 2; ++idx) {
    if (array[idx % length] == winner) {
      ++count;
      if (count == win_count) {
        std::cout << idx + 1 << " " << winner << std::endl;
        return;
      }
    } else {
      winner = array[idx % length];
      count = 1;
    }
  }
  std::cout << "INF" << std::endl;
}
int main() {
  int sample_num = 0;
  std::cin >> sample_num;
  while (sample_num-- > 0) {
    int length, win_count;
    std::cin >> length >> win_count;
    std::vector<int> arrays(length);
    bool all_same = true;
    std::cin >> arrays[0];
    for (auto idx = 1; idx < length; ++idx) {
      std::cin >> arrays[idx];
      all_same = (arrays[idx] == arrays[idx - 1]); 
    }
    if (all_same) {
      std::cout << win_count << " " << arrays[0] << std::endl;
      continue;
    }
    WhoWin(arrays, win_count);
  }
}