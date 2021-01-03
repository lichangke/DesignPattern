# 介绍

代理模式是常用的结构型设计模式之一，当无法直接访问某个对象或访问某个对象存在困难时可以通过一个代理对象来间接访问。代理模式又可以分为多种类型，例如保护代理、远程代理、虚拟代理、缓冲代理等，它们应用于不同的场合，满足用户的不同需求。

## 意图：

**代理模式：**给某一个对象提供一个代理或占位符，并由代理对象来控制对原对象的访问。

> Proxy Pattern: Provide a surrogate or placeholder for another object to control access to it.

## 解决问题：

代理模式根据其目的和实现方式不同可分为很多种类：

1. **远程代理（Remote Proxy）**：为一个位于不同地址空间的对象提供一个本地的代理对象。不同的地址空间可以在相同或不同的主机中。它使得客户端程序可以访问在远程主机上的对象，远程主机可能具有更好的计算性能与处理速度，可以快速响应并处理客户端的请求。
2. **虚拟代理（Virtual Proxy）**：对于一些占用系统资源较多或者加载时间较长的对象，可以先创建一个消耗相对较小的对象来表示，真实对象只在需要时才会被真正创建，而当真实对象创建之后，虚拟代理将用户的请求转发给真实对象。
3. **保护代理（Protect Proxy）**：给不同的用户提供不同的对象访问权限。
4. **缓冲代理（Cache Proxy）**：为某一个目标操作的结果提供临时存储空间，以使更多用户可以共享这些结果。
5. **智能引用代理（Smart Reference Proxy）**：当一个对象被引用时提供一些额外的操作，比如将对象被调用的次数记录下来等。

## 实现概述：

 代理模式的结构比较简单，其核心是代理类。一般都是采用代理类继承原始类，然后通过关联关系扩展附加功能。

## 应用场景：

(1) 当客户端对象需要访问远程主机中的对象时可以使用远程代理。
(2) 当需要用一个消耗资源较少的对象来代表一个消耗资源较多的对象，从而降低系统开销、缩短运行时间时可以使用虚拟代理，例如一个对象需要很长时间才能完成加载时。 
(3) 当需要为某一个被频繁访问的操作结果提供一个临时存储空间，以供多个客户端共享访问这些结果时可以使用缓冲代理。通过使用缓冲代理，系统无须在客户端每一次访问时都重新执行操作，只需直接从临时缓冲区获取操作结果即可。  
(4) 当需要控制对一个对象的访问，为不同用户提供不同级别的访问权限时可以使用保护代理。
(5) 当需要为一个对象的访问（引用）提供一些额外的操作时可以使用智能引用代理。

 

### 生活中场景

代购

### 软件中场景

在业务系统中开发一些非功能性需求，比如：监控、统计、鉴权、限流、事务、幂等、日志。

## 优点：

- 代理模式在客户端与目标对象之间起到一个中介作用和保护目标对象的作用；
- 代理对象可以扩展目标对象的功能；
- 代理模式能将客户端与目标对象分离，在一定程度上降低了系统的耦合度，增加了程序的可扩展性

## 缺点：

- 代理模式会造成系统设计中类的数量增加
- 在客户端和目标对象之间增加一个代理对象，会造成请求处理速度变慢；
- 增加了系统的复杂度；



# 模式结构

- **Subject（抽象主题角色）**：声明了真实主题和代理主题的共同接口，这样一来在任何使用真实主题的地方都可以使用代理主题，客户端通常需要针对抽象主题角色进行编程。
- **Proxy（代理主题角色）**：代理主题角色通过关联关系引用真实主题角色，因此可以控制和操纵真实主题对象；代理主题角色中提供一个与真实主题角色相同的接口（以在需要时代替真实主题角色），同时还可以在调用对真实主题对象的操作之前或之后增加新的服务和功能；
- **RealSubject（真实主题角色）**：定义了代理角色所代表的真实对象，在真实主题角色中实现了真实的业务操作，客户端可以通过代理主题角色间接调用真实主题角色中定义的操作。

![设计模式之代理模式](\upload\设计模式之代理模式\设计模式之代理模式.jpg)



# 代码示例

模拟在业务代码中添加日志功能

Subject（抽象主题角色）： Subject

Proxy（代理主题角色）：ProxySubject

RealSubject（真实主题角色）： RealSubject

附加功能： Log



## GitHub

[ProxyPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E4%BB%A3%E7%90%86%E6%A8%A1%E5%BC%8F/ProxyPattern)

## Subject（抽象主题角色）

```cpp
/// Subject（抽象主题角色）： Subject
class Subject {
public:
    virtual ~Subject() = default;
    virtual void business() = 0;
protected:
    Subject() = default;
};
```

## RealSubject（真实主题角色）

```cpp
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
```

## 附加功能： Log

```cpp
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
```

## Proxy（代理主题角色）

```cpp
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
```

## 测试

```cpp
int main() {
    Subject *subject;
    subject = new ProxySubject();
    subject->business();
    delete subject;
    return 0;
}
```

## 输出

![image-20210103212017020](\upload\设计模式之代理模式\A_设计模式之代理模式.png)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

