#include <iostream>
#include <stack>

struct TreeNode {
  TreeNode() {}
  TreeNode(int x) : val(x) {}
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;
  TreeNode* prev = nullptr;
  TreeNode* next = nullptr;
  int val = 0;
};

void inorder(TreeNode* node, TreeNode** head, TreeNode** cur) {
  if (!node) {
    return;
  }
  inorder(node->left, head, cur);
  if (*head == nullptr) {
    *head = node;
  }
  if (*cur == nullptr) {
    *cur = node;
  } else {
    (*cur)->next = node;
    node->prev = *cur;
    *cur = node;
  }
  inorder(node->right, head, cur);
}

TreeNode* inorder(TreeNode* node) {
  TreeNode* head = nullptr;
  TreeNode* cur = nullptr;
  auto cur_node = node;
  std::stack<TreeNode*> s;
  while (cur_node || !s.empty()) {
    while (cur_node) {
      s.push(cur_node);
      cur_node = cur_node->left;
    }
    if (!s.empty()) {
      auto tmp = s.top();
      s.pop();
      {
        if (!head) head = tmp;
        if (!cur) {
          cur = tmp;
        } else {
          cur->next = tmp;
          tmp->prev = cur;
          cur = tmp;
        }
      }
      cur_node = tmp->right;
    }
  }
  return head;
}

void show(TreeNode* head) {
  auto tmp = head;
  TreeNode* last = nullptr;
  while (tmp) {
    if (!tmp->next) {
      last = tmp;
    }
    std::cout << tmp->val << ","; 
    tmp = tmp->next;
  }
  std::cout << std::endl;
  while (last) {
    std::cout << last->val << ",";
    last = last->prev;
  }
  std::cout << std::endl;
}

int main() {
  TreeNode node1(1), node2(2), node3(3), node4(4), node5(5), node7(7);
  {
    node1.left = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;
    node3.right = &node7;
  }
  TreeNode* head = nullptr;
  TreeNode* cur = nullptr;
  // inorder(&node1, &head, &cur);
  head = inorder(&node1);
  show(head);

  return 0;
}

