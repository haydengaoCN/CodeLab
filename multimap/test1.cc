#include <iostream>
#include <utility>
#include <string>
#include <unordered_map>
#include <map>
 
int main() {
    std::multimap<std::string, std::string> mm;
    std::unordered_map<std::string, std::string> um;
    std::map<std::string, std::string> m;
 
    mm.emplace("a", "a1");
    mm.emplace("a", "a2");
    m.emplace("a", "a1");
    m.emplace("a", "a2");
    um.emplace("a", "a1");
    um.emplace("a", "a2");

 
    for (const auto &p : um) {
        std::cout << p.first << " => " << p.second << '\n';
    }

}
