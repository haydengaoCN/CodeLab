struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* removeElements(ListNode* head, int val) {
    auto cur_node = head;
    ListNode* parent_node = nullptr;
    while (cur_node) {
      if (cur_node->val != val) {
        parent_node = cur_node;
        cur_node = cur_node->next;
        continue;
      }
      auto next_node = cur_node->next;
      if (parent_node) {
        parent_node->next = next_node;
        delete cur_node;
        cur_node = next_node;
      } else {
        delete cur_node;
        cur_node = next_node;
        head = next_node;
      }
    }
    return head;
  }
};

int main() {
  return 0;
}
