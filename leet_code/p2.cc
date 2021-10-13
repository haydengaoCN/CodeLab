struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    ListNode* head = nullptr;
    ListNode* prev_node = nullptr;
    int rest_val = 0;
    while (l1 && l2) {
      int sum = l1->val + l2->val + rest_val;
      rest_val = sum / 10;
      ListNode* tmp = new ListNode(sum % 10);
      if (!head) head = tmp;
      if (!prev_node) {
        prev_node = tmp;
      } else {
        prev_node->next = tmp;
        prev_node = tmp;
      }
      l1 = l1->next;
      l2 = l2->next;
    }
    while (l1) {
      int sum = l1->val + rest_val;
      rest_val = sum / 10;
      ListNode* tmp = new ListNode(sum % 10);
      prev_node->next = tmp;
      prev_node = tmp;
      l1 = l1->next;
    }
    while (l2) {
      int sum = l2->val + rest_val;
      rest_val = sum / 10;
      ListNode* tmp = new ListNode(sum % 10);
      prev_node->next = tmp;
      prev_node = tmp;
      l2 = l2->next;
   }
   if (rest_val != 0) {
     ListNode* tmp = new ListNode(rest_val);
     prev_node->next = tmp;
   }
   return head;
  }
};

int main() {
}
