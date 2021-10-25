#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Trie {
 public:
  Trie() {
    root = new Node('0');
  }

  void insert(string word) {
    auto cur_node = root;
    for (const auto& ch : word) {
      if (cur_node->next[ch - 'a']) {
        cur_node = cur_node->next[ch - 'a'];
      } else {
        auto tmp = new Node(ch);
        cur_node->next[ch - 'a'] = tmp;
        cur_node = tmp;
      }
    }
    cur_node->is_one_word = true;
  }

  bool search(string word) {
    auto cur_node = root;
    for (const auto& ch : word) { 
      if (!cur_node->next[ch - 'a']) {
        return false;
      }
      cur_node = cur_node->next[ch - 'a'];
    }
    return cur_node->is_one_word;
  }

  bool startsWith(string prefix) {
    auto cur_node = root;
    for (const auto& ch : prefix) { 
      if (!cur_node->next[ch - 'a']) {
        return false;
      }
      cur_node = cur_node->next[ch - 'a'];
    }
    return true;
  }

 private:
  struct Node {
    Node(char ch) : val(ch) {
      next.resize(26, nullptr);
    }
    std::vector<Node*> next;
    char val;
    bool is_one_word{false};
  };
  Node* root{nullptr};
};

int main() {
  return 0; 
}
