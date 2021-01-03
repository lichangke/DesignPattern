//
// Created by leacock on 2021/1/3.
//

#ifndef PROXYPATTERN_PROXYPATTERN_H
#define PROXYPATTERN_PROXYPATTERN_H

#include <iostream>
#include <ctime>

/// Subject（抽象主题角色）： Subject
class Subject {
public:
    virtual ~Subject() = default;
    virtual void business() = 0;
protected:
    Subject() = default;
};

/// RealSubject（真实主题角色）： RealSubject
class RealSubject : public Subject {
public:
    RealSubject (){
        std::cout << "RealSubject Hello" << std::endl;
    }
    ~RealSubject () override{
        std::cout << "RealSubject Bye" << std::endl;
    }
    void business() override{
        std::cout << "business 业务代码在此执行" << std::endl;
    }

};

/// 附加功能： Log
class Log {
public:
    Log () {
        std::cout << "Log Hello" << std::endl;
    }
    ~Log () {
        std::cout << "Log Bye" << std::endl;
    }
    std::string addTimeLog() {
        time_t t = time(nullptr);
        char timeLog[64] = {0};
        std::strftime(timeLog, 63, "%Y-%m-%d %H:%M:%S",localtime(&t));
        return std::string(timeLog);
    }

};

/// Proxy（代理主题角色）：ProxySubject
class ProxySubject : public Subject {
public:
    ProxySubject (){
        std::cout << "ProxySubject Hello" << std::endl;
        realSubject = new RealSubject();
        log = new Log();
    }
    ~ProxySubject () override{
        std::cout << "ProxySubject Bye" << std::endl;
        delete realSubject;
        delete log;
    }
    void preBusiness() {
        std::cout << "preBusiness 被调用，时间为：" << log->addTimeLog() << std::endl;
    }
    void business() override {
        preBusiness();
        realSubject->business();
        std::cout << "输入任意键继续："  << std::endl;
        getchar();
        afterBusiness();
    }
    void afterBusiness() {
        std::cout << "afterBusiness 被调用，时间为：" << log->addTimeLog() << std::endl;
    }
private:
    RealSubject *realSubject;
    Log *log;
};



#endif //PROXYPATTERN_PROXYPATTERN_H
