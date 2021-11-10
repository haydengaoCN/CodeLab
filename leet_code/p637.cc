#include <iostream>
#include <vector>
#include <queue>

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
  vector<double> averageOfLevels(TreeNode* root) {
    std::vector<double> ans;
    if (!root) return ans;
    std::queue<TreeNode*> q;
    q.push(root);
    int cur_level_nodes = 1;
    while (!q.empty()) {
      int tmp = 0, tmp2 = cur_level_nodes;
      double sum = 0;
      while (tmp2 != 0) {
        auto node = q.front();
        q.pop();
        sum += node->val;
        if (node->left) {
          q.push(node->left);
          ++tmp;
        }
        if (node->right) {
          q.push(node->right);
          ++tmp;
        }
        --tmp2;
      }
      ans.emplace_back(sum / cur_level_nodes);
      cur_level_nodes = tmp;
    }
    return ans;
  }
};

int main() {
  return 0;
}
