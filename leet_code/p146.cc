#include <list>
#include <iostream>
#include <unordered_map>

class LRUCache {
 public:
  LRUCache(int capacity) {
    capacity_ = capacity;
  }
  
  int get(int key) {
    auto iter = dict_.find(key);
    if (iter == dict_.end()) {
      return -1;
    }
    touch(iter->second);
    return iter->second->val;
  }
  
  void put(int key, int value) {
    auto iter = dict_.find(key);
    if (iter != dict_.end()) {
      iter->second->val = value;
      touch(iter->second);
    } else {
      data_.push_front({key, value});
      dict_.emplace(key, data_.begin());
      if (dict_.size() > capacity_) {
        del();
      }
    }
  }

  void show() {
    for (const auto& node : data_) {
      std::cout << node.key << "," << node.val << std::endl;
    }
  }
  
private:
  struct Node {
    Node (int k, int v) : key(k), val(v) {}
    int key{0};
    int val{0};
  };
  
  void touch(std::list<Node>::iterator iter) {
    data_.splice(data_.begin(), data_, iter);
  }
  
  void del() {
    dict_.erase(data_.back().key);
    data_.pop_back();
  }

  
  int capacity_{0};
  std::list<Node> data_;
  std::unordered_map<int, std::list<Node>::iterator> dict_;
};

int main() {
  LRUCache lru{2};
  lru.put(1,1);
  lru.put(2,2);
  std::cout << lru.get(1) << std::endl;
  lru.show();
  lru.put(3,3);
  std::cout << lru.get(2) << std::endl;
  lru.show();
  lru.put(4,4);
  lru.get(1);
  lru.get(3);
  lru.get(4);
  lru.show();
  return 0;
}
