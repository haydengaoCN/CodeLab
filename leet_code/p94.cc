#include <iostream>
#include <stack>
#include <vector>

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
  vector<int> inorderTraversal(TreeNode* root) {
    sol(root);
    return ans;
  }
  
 private:
  std::vector<int> ans;
  void sol(TreeNode* root) {
    std::stack<TreeNode*> s;
    auto node = root;
    while (node || !s.empty()) {
      while (node) {
        s.push(node);
        std::cout << node << "," << node->val << std::endl;
        node = node->left;
      }
      if (!s.empty()) {
        node = s.top();
        std::cout << node << "," << node->val << std::endl;
        s.pop();
        ans.emplace_back(node->val);
        node = node->right;
      }
    }
  }
};

int main() {
  Solution sol;
  TreeNode root(0);
  sol.inorderTraversal(&root);
  return 0;
}
