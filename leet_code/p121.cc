#include <vector>
#include <algorithm>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices) {
    if (prices.empty()) {
      return 0;
    }
    int max_profit = 0;
    int min_stock = prices[0];
    for (auto idx = 1; idx < prices.size(); ++idx) {
      max_profit = std::max(prices[idx] - min_stock, max_profit);
      min_stock  = std::min(prices[idx], min_stock);
    }
    return max_profit;
  }
};

int main() {
}

