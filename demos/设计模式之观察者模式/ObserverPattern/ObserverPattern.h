//
// Created by leacock on 2021/1/11.
//

#ifndef OBSERVERPATTERN_OBSERVERPATTERN_H
#define OBSERVERPATTERN_OBSERVERPATTERN_H

#include <iostream>
#include <list>

class Blog;

/// Observer（观察者）:  Observer
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
protected:
    Observer() = default;
};


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

#endif //OBSERVERPATTERN_OBSERVERPATTERN_H
