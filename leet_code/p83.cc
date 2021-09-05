 #include <iostream>

 struct ListNode {
    int val;
    ListNode *next;
   ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        auto ret = head;
        auto cur_node = head;
        while(cur_node) {
            std::cout << cur_node << std::endl;
            auto next_node = cur_node->next;
            while (next_node && next_node->val == cur_node->val) {
                std::cout << next_node << std::endl;
                next_node == next_node->next;
            }
            if (!next_node) {
                cur_node->next = nullptr;
                return ret;
            }
            cur_node->next = next_node;
            cur_node = next_node;
        }
        return ret;
    }
};

int main () {
  ListNode node0(1), node1(2);
  node0.next = &node1;
  Solution sol;
  sol.deleteDuplicates(&node0);
  return 0;
}
}
