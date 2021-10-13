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
  int maxPathSum(TreeNode* root) {
    if (!root) return 0;
    int max_len = root->val;
    dfs(root);
    preorder(root, max_len);
    return max_len;
  }

 private:
   int dfs(TreeNode* root) {
     if (!root) return 0;
     root->val += std::max(std::max(dfs(root->left), dfs(root->right)), 0);
     return root->val;
   }
   void preorder(TreeNode* root, int& max_len) {
     if (!root) return;
     int left_val = root->left ? root->left->val : 0;
     int right_val = root->right ? root->right->val : 0;
     int cur_val = root->val + std::max(std::min(left_val, right_val), 0);
     max_len = std::max(cur_val, max_len);
     preorder(root->left, max_len);
     preorder(root->right, max_len);
   }
};

