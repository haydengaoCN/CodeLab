#include <string>
#include <vector>

std::string say_hi_stl = "hello world";
char say_hi_char[] = "hi world";

static const std::vector<std::string> greets_stl{"hello", "hi"};
static const char greets_char[][100] = {"hello", "hi"};

