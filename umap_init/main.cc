#include <iostream>
#include <unordered_map>
#include <map>
#include <string>

std::unordered_map<std::string, uint32_t> TNM2_ADTYPE_REQ_COUNT {
  {"LD", 1427139},
  {"BG", 1460785},  // todo
  {"KB", 1427217},
  {"FT", 1460786},  // todo
  {"TP", 1460789},  // todo
  {"ZT", 1427219},
  {"HT", 1427220},
  {"ZC", 1427221},
  {"WL", 1427222},
  {"WZ", 1427223},
  {"WH", 1427224},
  {"TL", 1427225},
  {"WK", 1427226},
  {"WC", 1427227},
  {"WI", 1460790},  // todo
  {"ZI", 1460791},  // todo
  {"TH", 1427228},
  {"TZ", 1427229},
  {"TI", 1460793},  // todo
  {"TK", 1427231},
  {"BS", 1460794},  // todo
  {"TJ", 1460796},  // todo
  {"Tflash", 1460799},  // todo
  {"TZC", 1460802},  // todo
  {"WBS", 1460803},  // todo
  {"WJ", 1460805},  // todo
  {"ZBC", 1460809},  // todo
  {"WD", 1460811},  // todo
  {"TM", 1460812},  // todo
  {"PSJ", 1460813},  // todo
  {"WSJ", 1460814},  // todo
  {"TSJ", 1460818},  // todo
  {"WVL", 1452946},
  {"WPB", 1452947},
  {"PVL", 1427235},
  {"PPB", 1452948},
  {"WDF", 1452949},
  {"PDF", 1452950},
  {"TVL", 1452952},
  {"TPB", 1452953},
  {"TCA", 1452954},
  {"CZC", 1460819},  // todo
  {"VM", 1460820},  // todo
  {"TDF", 1452956},
  {"PLJ", 1460821},  // todo
  {"WLJ", 1460822},  // todo
  {"WLF", 1427297},
  {"PLF", 1427298},
  {"TLF", 1427299},
  {"VIN", 1460838},  // todo
  {"PCZC", 1460839},  // todo
  {"WCZC", 1460840},  // todo
  {"TCZC", 1460841},  // todo
  {"SPLASH", 1427236},
  {"OuterPaster", 1427237},
  {"MobPlaySpeed", 1452957},
  {"TVOuterPaster", 1437381},
  {"others", 1427238}
};

int main() {
  std::cout << TNM2_ADTYPE_REQ_COUNT["LD"] << std::endl;
  for (auto elem : TNM2_ADTYPE_REQ_COUNT){
    std::cout << elem.first << "  " << elem.second << std::endl;
  }
  return 0;
}
