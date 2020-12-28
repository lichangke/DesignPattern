//
// Created by leacock on 2020/12/28.
//

#ifndef LAZYSINGLETON02_LAZYSINGLETON_H
#define LAZYSINGLETON02_LAZYSINGLETON_H

#include <iostream>

class LazySingleton {
public:
    static LazySingleton *getInstance() {
        static LazySingleton instance;
        return &instance;
    }

private:
    LazySingleton(){
        std::cout << "LazySingleton Hello" << std::endl;
    };
    ~LazySingleton() { // 私有化 可以避免 直接 delete s1 ，必须 使用 delInstance
        std::cout << "LazySingleton Bye" << std::endl;
    }
};
#endif //LAZYSINGLETON02_LAZYSINGLETON_H
