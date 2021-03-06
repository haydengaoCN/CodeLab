#include <iostream>
#include <vector>

void show(const std::vector<int>& vec) {
  for (const auto & num : vec) {
    std::cout << num << ",";
  }
  std::cout << std::endl;
}

void qs(std::vector<int>& nums, int left, int right) {
  if (left >= right) {
    return;
  }
  int pivot = nums[left];
  int l = left, r = right;
  while (l < r) {
    while (l < r && nums[r] >= pivot) {
      --r;
    }
    if (l < r) nums[l++] = nums[r];
    while ( l < r && nums[l] <= pivot) {
      ++l;
    }
    if (l < r) nums[r--] = nums[l];
  }
  nums[l] = pivot;
  show(nums);
  qs(nums, left, l - 1);
  qs(nums, l + 1, right);
}

int main() {
  std::vector<int> nums{5, 3, 0, 9, 1, 4, 3, 8};
  std::vector<int> nums2{1,2,3,4,5};
  std::vector<int> nums3{5,4,3,2,1};
  auto proxy = [](std::vector<int>& nums) {
    qs(nums, 0, nums.size() - 1);
    show(nums);
  };
  proxy(nums3);
  return 0;
}
