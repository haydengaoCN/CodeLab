#include <stdio.h>
#include <iostream>
#include <string>

    std::string str = "123";
    str += "4";

int main() {
    char arr[0];
    const char* pmd5 = "123";
    printf("%s\n", pmd5);
    std::cout << *pmd5 << std::endl;

    static const char pchar[]="123";
    std::cout << str << std::endl;

    return 0;
}
