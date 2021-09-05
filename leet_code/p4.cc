#include <vector>
#include <iostream>
#include <queue>

using namespace std;
class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    std::queue<int> min_heap;

    int tot_num = nums1.size() + nums2.size();
    bool is_even = (tot_num % 2) == 0;
    int num_need_in_heap = tot_num / 2 + 1;
    for (int heap_in_count = 0, idx1 = 0, idx2 = 0; heap_in_count < num_need_in_heap; ++heap_in_count) {
      auto val = NextNum(nums1, nums2, idx1, idx2);
      std::cout << "val:" << val << ", ";
      if (!min_heap.empty()) {
        std::cout << "back:" << min_heap.back() << ", front:" << min_heap.front() << std::endl;
      }
      if (min_heap.size() <= 2) {
        min_heap.push(val);
	    } else {
	      min_heap.pop();
	      min_heap.push(val);
	    }
    }

    double val1 = min_heap.front();
    min_heap.pop();
    double val2 = min_heap.front();

    return is_even ? (val1 + val2) / 2 : val2;
  }

 private:
  int NextNum(const std::vector<int>& nums1, const std::vector<int>& nums2, int& idx1, int& idx2) {
    if (idx1 < nums1.size() && idx2 < nums2.size()) {
      if (nums1[idx1] < nums2[idx2]) {
        return nums1[idx1++];
      }
      return nums2[idx2++];
    }
    if (idx1 < nums1.size()) {
      return nums1[idx1++];
    }
    return nums2[idx2++];
  }
};

int main() {
  std::vector<int> nums1{1, 3, 11}, nums2{4, 8, 10};
  Solution sol;
  std::cout << sol.findMedianSortedArrays(nums1, nums2) << std::endl;

  return 0;
}
