#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    prices.emplace_back(0);
    int profit = 0;
    int buy_in_price = -1;
    int idx = 0;
    while (idx < prices.size() - 1) {
      // find one vally
      while (idx < prices.size() - 1 && prices[idx] >= prices[idx + 1]) {
        ++idx;
      }
      buy_in_price = prices[idx];
      ++idx;
      while (idx < prices.size() - 1 && prices[idx] <= prices[idx + 1]) {
        ++idx; 
      }
      profit += prices[idx] - buy_in_price;
    }
    return profit;
  }
};

int main() {
  return 0;
}
