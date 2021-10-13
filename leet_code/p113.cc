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
  vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    std::vector<int> tmp;
    backtrace(root, tmp, targetSum);
    return ans;
  }
 private:
  std::vector<std::vector<int>> ans;
  void backtrace(TreeNode* root, std::vector<int>& tmp, int target) {
    if (!root) return;
    if (!root->left && !root->right) {
      if (root->val == target) {
        tmp.emplace_back(root->val);
        ans.emplace_back(tmp);
        tmp.pop_back();
      }
      return;
    }
    tmp.emplace_back(root->val);
    backtrace(root->left, tmp, target - root->val);
    backtrace(root->right, tmp, target - root->val);
    tmp.pop_back();
  }
};
