#include<time.h>
#include<stdlib.h>

#include<iostream>
#include<vector>
#include<string>

void test1() {
  srand(time(nullptr));
  float total_weight = 1e5;
  size_t vec_size = 4;
  std::vector<float> weight(vec_size, 0.0); 
  while(1) {
    float cur_sum_weight = 0.0;
    for (auto& val : weight) {
      val = total_weight * 0.24 + (rand() % (2000));
      cur_sum_weight += val;
    }
    
    if (cur_sum_weight < total_weight) {
        continue;
    }

    float new_cur_sum_weight = 0.0;
    float ratio = total_weight / cur_sum_weight;
    for(auto val : weight) {
        auto tmp = val * ratio;
        std::cout << val << " -> " << tmp << std::endl;
        new_cur_sum_weight += tmp;
    }

    std::cout << "after adjust, weight_sum:" << new_cur_sum_weight << ", delta:" << total_weight - new_cur_sum_weight << std::endl;

    getchar();
  }
}

void test2() {
  std::string val_bin = "0.00011001100110011001100";
  double val_dec = 0.0;
  double start = 1.0;
  for (auto idx = 2; idx < val_bin.size(); ++idx) {
      start /= 2;
    if (val_bin[idx] == 1) {
      val_dec += start;
    }
  }  // end for
  std::cout << "val_dec:" << std::to_string(val_dec) << std::endl;
}
int main() {
  test2();

  return 0;
}