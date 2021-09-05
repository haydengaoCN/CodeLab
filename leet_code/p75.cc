#include <vector>
#include <iostream>

using namespace std;

class Solution {
 public:
  void sortColors(vector<int>& nums) {
    sol2(nums);
  }


 private:
  void swap(std::vector<int>& nums, int p1, int p2) {
    auto tmp = nums[p1];
    nums[p1] = nums[p2];
    nums[p2] = tmp;
  }

  void sol1(vector<int>& nums) {
    std::vector<int> index{0, 0, 0};
    for_each(nums.begin(), nums.end(), [&index](int val) { ++index[val]; });
    index[2] = index[0] + index[1];
    index[1] = index[0];
    index[0] = 0;

    int index0 = index[0], index1 = index[1], index2 = index[2];
    while (index[0] < index1) {
	    int cur_val = nums[index[0]];
      if (cur_val == 0) {
        ++index[0];
	    } else {
	      swap(nums, index[0], index[cur_val]);
	      ++index[cur_val];
	    }
	  }
	  while (index[1] < index2) {
	    int cur_val = nums[index[1]];
	    if (cur_val == 1) {
	      ++index[1];
	    } else {
	      swap(nums, index[1], index[cur_val]);
	      ++index[cur_val];
	    }
	  }
	}
	
	void sol2(std::vector<int>& nums) {
	  int index0 = 0, index2 = nums.size() - 1;
	  for (auto idx = 0; idx < index2;) {
	    if (nums[idx] == 1) {
	      ++idx;
	      continue;
	    }
	    if (nums[idx] == 0) {
	      swap(nums, idx, index0++);
	      if (nums[idx] != 2) {
	        ++idx;
		      continue;
		    }
	    }
	    if (nums[idx] == 2) {
	      swap(nums, idx, index2--);
	      if (nums[idx] != 1) {
	        ++idx;
		      continue;
		    }
	    }
	  }
	}

	 void sol3(vector<int>& nums) {
		 int numSize = nums.size();
		 int pos0 = -1, pos2 = numSize;
		 for (int idx = 0; idx < pos2; idx++) {
			 if (nums[idx] == 0) {
				 swap(nums[idx], nums[++pos0]);
			 }
			 if (nums[idx] == 2) {
				 swap(nums[idx], nums[--pos2]);
				 idx--;
			 }
		 }
	 }
};

int main() {
  Solution sol;
  std::vector<int> vec{2, 0, 2, 1, 1, 0};
  sol.sortColors(vec);
  for_each(vec.begin(), vec.end(), [](const int val) { std::cout << val << ",";});
  std::cout << std::endl;

  return 0;
}
