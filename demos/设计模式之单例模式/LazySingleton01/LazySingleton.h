//
// Created by leacock on 2020/12/28.
//

#ifndef LAZYSINGLETON01_LAZYSINGLETON_H
#define LAZYSINGLETON01_LAZYSINGLETON_H

#include <iostream>
#include <mutex>

class LazySingleton {
public:
    static LazySingleton *getInstance() {
        //第一个检查，如果只是读操作，就不许用加锁
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lck(m_mutex);
            //第二个检查，保证只有一个
            if (instance == nullptr) {
                instance = new LazySingleton;
            }
        }
        return instance;
    }
    static void delInstance() {
        if(instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
private:
    LazySingleton(){
        std::cout << "LazySingleton Hello" << std::endl;
    };
    ~LazySingleton() { // 私有化 可以避免 直接 delete s1 ，必须 使用 delInstance
        std::cout << "LazySingleton Bye" << std::endl;
    }
    // static对象，可以保证对象只生成一次
    static LazySingleton *instance;
    static std::mutex m_mutex;
};

LazySingleton* LazySingleton::instance = nullptr;
std::mutex LazySingleton::m_mutex;

#endif //LAZYSINGLETON01_LAZYSINGLETON_H
