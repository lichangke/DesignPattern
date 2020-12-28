#include "LazySingleton.h"

int main() {
    LazySingleton *s1 = LazySingleton::getInstance();
    LazySingleton *s2 = LazySingleton::getInstance();

    std::cout << "s1 address = " << s1 << std::endl;
    std::cout << "s2 address = " << s2 << std::endl;


    getchar();
    return 0;
}
