#include "EagerSingleton.h"

int main() {
    EagerSingleton *s1 = EagerSingleton::getInstance();
    EagerSingleton *s2 = EagerSingleton::getInstance();

    std::cout << "s1 address = " << s1 << std::endl;
    std::cout << "s2 address = " << s2 << std::endl;

    EagerSingleton::delInstance();

    getchar();
    return 0;
}
