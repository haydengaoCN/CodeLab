#include <iostream>
#include <string>
#include <chrono>

const std::string kPrefix = "all_placement_group_id";

void foo(int index, std::string* key) {
  std::string idx = (index < 10) ?
      (std::to_string(0) + std::to_string(index)) : std::to_string(index);
  *key = kPrefix + "_" + idx;
}
void foo2(int index, std::string* key) {
  static const char kLackOrderKeys[100][100] = {
    "all_placement_group_id_00", "all_placement_group_id_01", "all_placement_group_id_02",
    "all_placement_group_id_03", "all_placement_group_id_04", "all_placement_group_id_05",
    "all_placement_group_id_06", "all_placement_group_id_07", "all_placement_group_id_08",
    "all_placement_group_id_09", "all_placement_group_id_10", "all_placement_group_id_11",
    "all_placement_group_id_12", "all_placement_group_id_13", "all_placement_group_id_14",
    "all_placement_group_id_15", "all_placement_group_id_16", "all_placement_group_id_17",
    "all_placement_group_id_18", "all_placement_group_id_19", "all_placement_group_id_20",
    "all_placement_group_id_21", "all_placement_group_id_22", "all_placement_group_id_23",
    "all_placement_group_id_24", "all_placement_group_id_25", "all_placement_group_id_26",
    "all_placement_group_id_27", "all_placement_group_id_28", "all_placement_group_id_29",
    "all_placement_group_id_30", "all_placement_group_id_31", "all_placement_group_id_32",
    "all_placement_group_id_33", "all_placement_group_id_34", "all_placement_group_id_35",
    "all_placement_group_id_36", "all_placement_group_id_37", "all_placement_group_id_38",
    "all_placement_group_id_39", "all_placement_group_id_40", "all_placement_group_id_41",
    "all_placement_group_id_42", "all_placement_group_id_43", "all_placement_group_id_44",
    "all_placement_group_id_45", "all_placement_group_id_46", "all_placement_group_id_47",
    "all_placement_group_id_48", "all_placement_group_id_49", "all_placement_group_id_50",
    "all_placement_group_id_51", "all_placement_group_id_52", "all_placement_group_id_53",
    "all_placement_group_id_54", "all_placement_group_id_55", "all_placement_group_id_56",
    "all_placement_group_id_57", "all_placement_group_id_58", "all_placement_group_id_59",
    "all_placement_group_id_60", "all_placement_group_id_61", "all_placement_group_id_62",
    "all_placement_group_id_63", "all_placement_group_id_64", "all_placement_group_id_65",
    "all_placement_group_id_66", "all_placement_group_id_67", "all_placement_group_id_68",
    "all_placement_group_id_69", "all_placement_group_id_70", "all_placement_group_id_71",
    "all_placement_group_id_72", "all_placement_group_id_73", "all_placement_group_id_74",
    "all_placement_group_id_75", "all_placement_group_id_76", "all_placement_group_id_77",
    "all_placement_group_id_78", "all_placement_group_id_79", "all_placement_group_id_80",
    "all_placement_group_id_81", "all_placement_group_id_82", "all_placement_group_id_83",
    "all_placement_group_id_84", "all_placement_group_id_85", "all_placement_group_id_86",
    "all_placement_group_id_87", "all_placement_group_id_88", "all_placement_group_id_89",
    "all_placement_group_id_90", "all_placement_group_id_91", "all_placement_group_id_92",
    "all_placement_group_id_93", "all_placement_group_id_94", "all_placement_group_id_95",
    "all_placement_group_id_96", "all_placement_group_id_97", "all_placement_group_id_98",
    "all_placement_group_id_99"};
    *key = kLackOrderKeys[index];
}

int main() {
  size_t retry_time = 1000;
  auto time0 = std::chrono::steady_clock::now();
  for (auto idx = 0; idx < retry_time; ++idx) {
    std::string key;
    foo(2, &key);
  }
  auto time1 = std::chrono::steady_clock::now();
  auto delta_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time0).count();
  auto delta_in_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time1 - time0).count();
  std::cout << "foo: " << delta_in_ns << std::endl;
  
  auto time2 = std::chrono::steady_clock::now();
  for (auto idx = 0; idx < retry_time; ++idx) {
    std::string key;
    foo2(2, &key);
  }
  auto time3 = std::chrono::steady_clock::now();
  auto delta_in_ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(time3 - time2).count();
  auto delta_in_ns2 = std::chrono::duration_cast<std::chrono::nanoseconds>(time3 - time2).count();
  std::cout << "foo2:" << delta_in_ns2 << std::endl;

  return 0;
}
