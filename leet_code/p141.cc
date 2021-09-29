#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  bool hasCycle(ListNode *head) {
    if (!head || !head->next) {
      return false;
    }
    auto slow_iter = head;
    auto quick_iter = head->next->next;
    while (quick_iter) {
      if (slow_iter == quick_iter) {
        return true;
      }
      quick_iter = quick_iter->next;
      if (!quick_iter) {
        return false;
      }
      quick_iter = quick_iter->next;
      slow_iter = slow_iter->next;
    }
    return false;
  }
};

int main() {
  return 0;
}
