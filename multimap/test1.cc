#include <iostream>
#include <utility>
#include <string>
#include <map>
 
int main() {
    std::multimap<std::string, std::string> mm;
    std::map<std::string, std::string> m;
 
    mm.emplace("a", "a1");
    mm.emplace("a", "a2");
    m.emplace("a", "a1");
    m.emplace("a", "a2");

 
    bool flag = false;
    const auto& t = flag ? mm : m;
    for (const auto &p : t) {
        std::cout << p.first << " => " << p.second << '\n';
    }

}
