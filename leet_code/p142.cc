#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode *detectCycle(ListNode *head) {
    ListNode* meeting = nullptr;
    if (!hasCycle(head, meeting)) {
      return nullptr;;
    }
    std::cout << meeting->val << std::endl;

    auto cur_node = head;
    while (cur_node != meeting) {
      cur_node = cur_node->next;
      meeting = meeting->next;
    }
    return cur_node;
  }
 
 private:
  bool hasCycle(ListNode* head, ListNode* meeting) {
    if (!head || !head->next) {
      return false;
    }
    auto slow_iter = head;
    auto quick_iter = head->next->next;
    while (quick_iter) {
      if (slow_iter == quick_iter) {
        meeting = slow_iter;
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
