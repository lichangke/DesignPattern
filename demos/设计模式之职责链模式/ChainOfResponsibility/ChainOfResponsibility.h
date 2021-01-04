//
// Created by leacock on 2021/1/4.
//

#ifndef CHAINOFRESPONSIBILITY_CHAINOFRESPONSIBILITY_H
#define CHAINOFRESPONSIBILITY_CHAINOFRESPONSIBILITY_H

#include <iostream>

/// 请求：Bill
class Bill {

public:
    Bill(int id, const std::string &name, double account){
        this->id = id;
        this->name = name;
        this->amount = account;
        std::cout << "Bill Hello," << "id = " << this->id
        << " name = " << this->name << " amount = " << this->amount  << std::endl;
    }
    ~Bill() {
        std::cout << "Bill Bye," << "id = " << this->id
                  << " name = " << this->name << " amount = " << this->amount  << std::endl;
    }
    double getAccount(){
        return amount;
    }
    void showBill(){
        std::cout << "Bill id = " << id << ", Bill name = " << name << ", Bill amount = " << amount  << std::endl;
    }
private:
    int id;
    std::string name;
    double amount;

};


/// Handler（抽象处理者）：AbstractHandler
class AbstractHandler {
public:

    explicit AbstractHandler(const std::string &name){
        setName(name);
        nextHandler = nullptr;
    }

    virtual ~AbstractHandler() = default;

    // 添加上级,职责链上的下一个处理者
    void setNextHandler(AbstractHandler *next) {
        nextHandler = next;
    }
    // 处理请求
    virtual void handleRequest(Bill* bill) = 0;

    std::string getName(){
        return name;
    }

protected:
    AbstractHandler *nextHandler;
private:
    void setName(const std::string &iName){
        this->name = iName;
    }
    std::string name;
};


/// ConcreteHandler（具体处理者）：TeamLeader、Supervisor、Manager、Boss
class TeamLeader : public AbstractHandler {

public:
    explicit TeamLeader(const std::string &name) : AbstractHandler(name) {
        std::cout << "TeamLeader Hello, " << name << std::endl;
    }
    ~TeamLeader() override {
        std::cout << "TeamLeader Bye, " << getName() << std::endl;
    }

    // 处理请求
    void handleRequest(Bill *bill) override{
        if (bill->getAccount() <= 10){
            std::cout << "TeamLeader " << getName() <<"处理了该票据，票据信息如下：" << std::endl;
            bill->showBill();
        } else {
            std::cout << "TeamLeader " << getName() <<" 无权处理，转交上级" << std::endl;
            if(nullptr == nextHandler) {
                std::cout << "票据无人处理，票据信息如下：" << std::endl;
                bill->showBill();
            }
            else {
                nextHandler->handleRequest(bill);
            }
        }
    }
};

class Supervisor : public AbstractHandler {

public:
    explicit Supervisor(const std::string &name) : AbstractHandler(name) {
        std::cout << "Supervisor Hello, " << name << std::endl;
    }
    ~Supervisor() override {
        std::cout << "Supervisor Bye, " << getName() << std::endl;
    }

    // 处理请求
    void handleRequest(Bill *bill) override{
        if ( 10 < bill->getAccount() && bill->getAccount() <= 20){
            std::cout << "Supervisor " << getName() <<"处理了该票据，票据信息如下：" << std::endl;
            bill->showBill();
        } else {
            std::cout << "Supervisor " << getName() <<" 无权处理，转交上级" << std::endl;
            if(nullptr == nextHandler) {
                std::cout << "票据无人处理，票据信息如下：" << std::endl;
                bill->showBill();
            }
            else {
                nextHandler->handleRequest(bill);
            }
        }
    }
};

class Manager : public AbstractHandler {

public:
    explicit Manager(const std::string &name) : AbstractHandler(name) {
        std::cout << "Manager Hello, " << name << std::endl;
    }
    ~Manager() override {
        std::cout << "Manager Bye, " << getName() << std::endl;
    }

    // 处理请求
    void handleRequest(Bill *bill) override{
        if ( 20 < bill->getAccount() &&  bill->getAccount() <= 50){
            std::cout << "Manager " << getName() <<"处理了该票据，票据信息如下：" << std::endl;
            bill->showBill();
        } else {
            std::cout << "Manager " << getName() <<" 无权处理，转交上级" << std::endl;
            if(nullptr == nextHandler) {
                std::cout << "票据无人处理，票据信息如下：" << std::endl;
                bill->showBill();
            }
            else {
                nextHandler->handleRequest(bill);
            }
        }
    }
};

class Boss : public AbstractHandler {

public:
    explicit Boss(const std::string &name) : AbstractHandler(name) {
        std::cout << "Boss Hello, " << name << std::endl;
    }
    ~Boss() override {
        std::cout << "Boss Bye, " << getName() << std::endl;
    }

    // 处理请求
    void handleRequest(Bill *bill) override{
        if ( 50 < bill->getAccount() && bill->getAccount() <= 100 ){
            std::cout << "Boss " << getName()  <<"处理了该票据，票据信息如下：" << std::endl;
            bill->showBill();
        } else {
            std::cout << "Boss " << getName() <<" 条件不满足，无法处理" << std::endl;
            if(nullptr == nextHandler) {
                std::cout << "票据无人处理，票据信息如下：" << std::endl;
                bill->showBill();
            }
            else {
                nextHandler->handleRequest(bill);
            }
        }
    }
};

#endif //CHAINOFRESPONSIBILITY_CHAINOFRESPONSIBILITY_H
