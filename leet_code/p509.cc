class Solution {
 public:
  int fib(int n) {
    int prev2 = 0, prev = 1;
    if (n == 0) {
      return prev2;
    }
    if (n == 1) {
      return prev;
    }
    for (auto idx = 2; idx <= n; ++idx) {
      int result = prev2 + prev;
      prev2 = prev;
      prev = result;
    }
    return prev;
  }
};
