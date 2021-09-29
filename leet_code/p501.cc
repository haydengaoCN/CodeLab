#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

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
  std::vector<int> findMode(TreeNode* root) {
  }

 private:
  void InOrder(TreeNode* root, bool is_first_round) {
    if (!root) {
      return;
    }
    InOrder(root->left, is_first_round);
    if (is_first_round) {
      Process1(root->val);
    } else {
      Process2(root->val);
    }
    InOrder(root->right, is_first_round);
  }

  void Process1(const int val) {
    if (max_count == -1) {
      cur_count = 1;
      cur_val = val;
      max_count = 1;
      return;
    }
    if (cur_val == val) {
      ++cur_count;
    } else {
      max_count = std::max(max_count, cur_count);
      cur_count = 1;
      cur_val = val;
    }
  }

  void Process2(const int val) {
    
  }

  std::vector<int> ans;
  int cur_val = 0, cur_count = 0, max_count = -1;
};
