#include <iostream>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    std::vector<std::vector<int>> ans;
    if (!root) return ans;
    std::stack<TreeNode*> s1,s2;
    s1.push(root);
    int level = 0;
    while (!s1.empty()) {
      ans.emplace_back({});
      auto& tmp = ans.back();
      while (!s1.empty()) {
        auto node = s1.top();
        s1.pop();
        tmp.emplace_back(node->val);
        if (level % 2 == 0) {
          if (node->left) s2.push(node->left);
          if (node->right) s2.push(node->right);
        } else {
          if (node->right) s2.push(node->right);
          if (node->left) s2.push(node->left);
        }
      }
      ++level;
      s1.swap(s2);
    }
    return ans;
  }
};
