//
// Created by leacock on 2020/12/28.
//

#ifndef EAGERSINGLETON_EAGERSINGLETON_H
#define EAGERSINGLETON_EAGERSINGLETON_H

#include <iostream>

class EagerSingleton {
public:

    static EagerSingleton *getInstance(){
        return instance;
    }
    static void delInstance() {
        if(instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
private:
    EagerSingleton(){
        std::cout << "EagerSingleton Hello" << std::endl;
    };
    ~EagerSingleton() { // 私有化 可以避免 直接 delete s1 ，必须 使用 delInstance
        std::cout << "EagerSingleton Bye" << std::endl;
    }
    // static对象，可以保证对象只生成一次,并且是多线程安全
    static EagerSingleton *instance;
};

EagerSingleton *EagerSingleton::instance = new EagerSingleton();


#endif //EAGERSINGLETON_EAGERSINGLETON_H

