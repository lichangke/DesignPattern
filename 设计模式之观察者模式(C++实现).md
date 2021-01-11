更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

[TOC]

# 介绍

软件系统中的对象不是孤立存在的他们相互之间会有联系，一个对象行为的改变可能会引起其他所关联的对象的状态或行为也发生改变。观察者模式让一个对象改变时自动通知其他对象，其他对象将作出相应反应，建立了一种一对多的联动。

观察者模式包含**观察目标和观察者两类对象**，一个观察目标可以有任意数目的与之相依赖的观察者，一旦观察目标的状态发生改变，所有的观察者都将得到通知。

## 意图：

**观察者模式(Observer Pattern)：** 定义对象之间的一种一对多依赖关系，使得每当一个对象状态发生改变时，其相关依赖对象皆得到通知并被自动更新。观察者模式的别名包括发布-订阅（Publish/Subscribe）模式、模型-视图（Model/View）模式、源-监听器（Source/Listener）模式或从属者（Dependents）模式。



## 解决问题：

一个对象状态改变，需要给其他对象通知的问题

## 实现概述：

需要定义一个抽象目标Subject，具体目标类ConcreteSubject是其子类。

抽象观察者角色Observer通常只声明一个update()方法，为不同观察者的更新（响应）行为定义相同的接口，这个方法在其子类ConcreteObserver（具体观察者）中实现，不同的观察者具有不同的响应方法。



## 应用场景：

- 一个对象的改变将**导致一个或多个其他对象也发生改变**，而并不知道具体有多少对象将发生改变，也不知道这些对象是谁。
- 如果需要设计一个**链式触发的系统**，A对象的行为将影响B对象，B对象的行为将影响C对象……，可是使用观察者模式；



## 优点：

- 观察者模式实现了稳定的**消息更新和传递的机制**，通过引入抽象层可以扩展不同的具体观察者角色；
- 观察者模式在观察目标和观察者之间建立一个**抽象的耦合**。观察目标只需要维持一个抽象观察者的集合，无须了解其具体观察者。
- **支持广播通信**，所有已注册的观察者（添加到目标列表中的对象）都会得到消息更新的通知，**简化了一对多设计的难度**；
- 增加新的具体观察者无须修改原有系统代码，**符合开闭原则**，在具体观察者与观察目标之间不存在关联关系的情况下增加新的观察目标也很方便。

## 缺点：

- **观察者和观察目标相互引用**，存在循环依赖，如果处理不当有引起系统崩溃的风险；
- 如果一个观察目标对象有很多直接和间接观察者，将所有的观察者都通知到会耗费大量时间。
- 观察者不知道所观察的目标对象是怎么发生变化的，而仅仅只是知道观察目标发生了变化。

# 模式结构

## 角色

- **Subject（目标）**：被观察的对象，其中定义了一个观察者的集合，即一个目标可能会有多个观察者，提供相应方法来增删观察者对象。并声明了通知方法，比如notify()，用于在自身状态发生改变时通知观察者。
- **ConcreteSubject（具体目标）**：具体目标是目标类的子类，包含有发生改变的数据。当状态发生改变时，向它的各个观察者发出通知 notify()。如果有的话，它同时还实现了在目标类中定义的抽象业务逻辑方法。
- **Observer（观察者）**：抽象观察者，声明了更新数据的方法，比如update()，对观察目标的改变做出反应。
- **ConcreteObserver（具体观察者）**： 实现了更新方法，比如update()，具体观察者中维护了一个具体目标对象的引用（指针），用于存储目标的状态。

## 类图

![设计模式之观察者模式](\upload\设计模式之观察者模式\设计模式之观察者模式.jpg)



# 代码示例

模拟博客订阅功能，当博主更新了博客，自动通知所有订阅者

Subject（目标）： Blog 

ConcreteSubject（具体目标）:  BlogCSDN 

Observer（观察者）:  Observer  

ConcreteObserver（具体观察者）： ObserverBlog 



## GitHub

[ObserverPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E8%A7%82%E5%AF%9F%E8%80%85%E6%A8%A1%E5%BC%8F/ObserverPattern)

## Subject（目标）

```cpp
/// Subject（目标）： Blog
class Blog {
public:
    virtual ~Blog() = default;
    void attach(Observer *observer) { //添加观察者
        observerList.push_back(observer);
    }
    void remove(Observer *observer) { //移除观察者
        observerList.remove(observer);
    }
    void notify() { //通知观察者
        for(auto observer:observerList) {
            observer->update();
        }
    }
    virtual void setStatus(std::string s) = 0;
    virtual std::string getStatus() = 0;   //获得状态
private:
    std::list<Observer* > observerList; //观察者链表
protected:
    Blog() = default;
    std::string status; //状态
};
```



## ConcreteSubject（具体目标）

```cpp
/// ConcreteSubject（具体目标）:  BlogCSDN
class BlogCSDN : public Blog
{

public:
    explicit BlogCSDN(const std::string &name) {
        this->name = name;
        std::cout << "BlogCSDN Hello,name = " << this->name << std::endl;
    }
    ~BlogCSDN() override {
        std::cout << "BlogCSDN Bye,name = " << this->name << std::endl;
    }
    void setStatus(std::string s) override {  //具体设置状态信息
        status = "CSDN通知 : " + name + s;
    }
    std::string getStatus() override {
        return status;
    }

private:
    std::string name; //博主名称
};
```



## Observer（观察者）

```cpp
/// Observer（观察者）:  Observer
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
protected:
    Observer() = default;
};
```



## ConcreteObserver（具体观察者）

```cpp
///ConcreteObserver（具体观察者）： ObserverBlog
class ObserverBlog : public Observer {
public:
    explicit ObserverBlog(const std::string &name,Blog *blog) {
        this->name = name;
        this->blog = blog;
        std::cout << "ObserverBlog Hello,name = " << this->name << std::endl;
    }
    ~ObserverBlog() override {
        std::cout << "ObserverBlog Bye,name = " << this->name << std::endl;
    }

    void update() override{ //获得更新状态
        std::string status = blog->getStatus();
        std::cout<< name <<"-------"<< status<<std::endl;
    }

private:
    std::string name;  //观察者名称
    Blog *blog;
};

```





## 测试

```cpp
int main() {
    Blog *blog = new BlogCSDN("墨1024");
    Observer *observer1 = new ObserverBlog("张三",blog);
    Observer *observer2 = new ObserverBlog("李四",blog);
    blog->attach(observer1);
    blog->attach(observer2);
    std::cout << "==================" << std::endl;
    blog->setStatus("发表了一篇Blog");
    blog->notify();
    std::cout << "==================" << std::endl;
    blog->remove(observer1);
    blog->setStatus("更新了一条blink");
    blog->notify();
    std::cout << "==================" << std::endl;
    delete blog;
    delete observer1;
    delete observer2;
    return 0;
}
```



## 输出

![image-20210111145149431](\upload\设计模式之观察者模式\A_设计模式之观察者模式.png)

*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

