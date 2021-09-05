#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
n0 - n1 - n2 - n3
*/
class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto cur_node = head;
    auto next_k_node = head;

    int step = 1;
    while (step < n && next_k_node) {
      next_k_node = next_k_node->next;
      ++step;
    }
    if (step != n || !next_k_node) {
      return nullptr;
    }

    ListNode* parent_node = nullptr;
    while (next_k_node->next) {
      parent_node = cur_node;
      cur_node = cur_node->next;
      next_k_node = next_k_node->next;
    }
    if (parent_node) {
      parent_node->next = cur_node->next;
      return head;
    }
    return head->next;
  }
};

int main() {
  return 0;
}
