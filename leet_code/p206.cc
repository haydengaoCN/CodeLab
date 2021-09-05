struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
parent - cur - next
*/
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) {
      return head;
    }
    auto cur_node = head->next;
    auto parent_node = head;
    head->next = nullptr;
    while (cur_node) {
      auto next_node = cur_node->next;
      cur_node->next = parent_node;
      parent_node = cur_node;
      cur_node = next_node;
    }
    return parent_node;
  }
};

int main() {
  return 0;
}
