#include <vector>
#include <iostream>

using namespace std;
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
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.empty()) return nullptr;
    return helper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
  }

 private:
  TreeNode* helper(
      std::vector<int>& preorder, int left1, int right1,
      std::vector<int>& inorder,  int left2, int right2) {
    std::cout << left1 << " " << right1 << " " << left2 << " " << right2 << std::endl;
    if (left1 > right1 || left2 > right2) {
      return nullptr;
    }
    auto root = new TreeNode(preorder[left1]);
    int pos_root = [&]() {
      int tmp = left2;
      while (inorder[tmp] != root->val) {
        ++tmp;
      }
      return tmp;
    }();
    root->left  = helper(preorder, left1 + 1, pos_root + left1 - left2,
                         inorder,  left2, pos_root - 1);
    root->right = helper(preorder, pos_root + left1 - left2 + 1, right1,
                         inorder, pos_root + 1, right2);
    return root;
  }
};

void show(TreeNode* root) {
  if (!root) return;
  std::cout << root->val << ",";
  show(root->left);
  show(root->right);
}

int main() {
  std::vector<int> preorder{3,9,20,15,7};
  std::vector<int> inorder{9,3,15,20,7};
  Solution sol;
  auto node = sol.buildTree(preorder, inorder);
  show(node);
  std::cout << std::endl;
  return 0;
}
