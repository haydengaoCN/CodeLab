#include <iostream>
#include <vector>

using namespace std;
class Solution {
 public:
  bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    if ( flowerbed.empty()) {
      return n == 0;
    }
    auto idx = 0;
    flowerbed.emplace_back(0);
    int prev = 0;
    while ( n != 0 && idx < flowerbed.size() - 1) {
      if (prev == 0 && flowerbed[idx] == 0 && flowerbed[idx + 1] == 0) {
        flowerbed[idx] = 1;
        --n;
      }
      prev = flowerbed[idx];
      ++idx;
    }
    return n == 0;
  }
};

int main() {
  return 0; 
}
