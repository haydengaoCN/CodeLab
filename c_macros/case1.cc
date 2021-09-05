#define CONCAT2(str1, str2) str1##str2

#define CreateRainbowOption(var_name, type, val)                    \
  CONCAT2(var_name, _) = std::make_unique<DynamicRainbowOption<type>>(   \
      group, var_name, val)

int main() {
  CreateRainbowOption(qqlive_vip_adid_list, std::string, "1");
}
#undef CreateRainbowOption
