#include <iostream>
#include <algorithm>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
 public:
  ListNode* sortList(ListNode* head) {
    return mergesort(head);
  }
 
 ListNode* merge(ListNode* node1, ListNode* node2) {
   if (!node1) {
     return node2;
   }
   if (!node2) {
     return node1;
   }
   ListNode* result = nullptr;
   if (node1->val < node2->val) {
     result = node1;
     result->next = merge(node1->next, node2);
   } else {
     result = node2;
     result->next = merge(node1, node2->next);
   }
   return result;
 }
 ListNode* mergesort(ListNode* node) {
   if (!node || !node->next) {
     return node;
   }
   auto [node1, node2] = pivot(node);
   std::cout << node1->val << "," << node2->val << std::endl;
   auto head1 = mergesort(node1);
   auto head2 = mergesort(node2);
   return merge(head1, head2);
 }
 std::pair<ListNode*, ListNode*> pivot(ListNode* node) {
   if (!node) {
     return {nullptr, nullptr};
   }
   if (!node->next) {
     return {node, nullptr};
   }
   auto slow = node;
   auto quick = node;
   while (quick && quick->next && quick->next->next) {
     slow = slow->next;
     quick = quick->next->next;
   }
   auto next = slow->next;
   slow->next = nullptr;
   return {node, next};
 }
 public:
 void show(ListNode* node) {
   while (node) {
     std::cout << node->val << ",";
     node = node->next;
   }
   std::cout << std::endl;
 }
};

int main() {
  ListNode node1(3), node2(1), node3(2);
  node1.next = &node2;
  node2.next = &node3;

  Solution sol;
  auto head = sol.sortList(&node1);
  sol.show(head);
  return 0;
}

