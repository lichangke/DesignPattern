更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍

职责链可以是一条直线、一个环或者一个树形结构，最常见的职责链是直线型，即沿着一条单向的链来传递请求。链上的每一个对象都是请求处理者，职责链模式可以将请求的处理者组织成一条链，并让请求沿着链传递，由链上的处理者对请求进行相应的处理，**客户端无须关心请求的处理细节以及请求的传递，只需将请求发送到链上即可，实现请求发送者和请求处理者解耦。**

## 意图：

**职责链模式(Chain of Responsibility  Pattern)**：避免请求发送者与接收者耦合在一起，让多个对象都有可能接收请求，将这些对象连接成一条链，并且沿着这条链传递请求，直到有对象处理它为止。

## 解决问题：

将请求的发送和接收解耦，让多个接收对象都有机会处理这个请求。

## 实现概述：

职责链模式核心在于引入了一个抽象处理者。通常每个处理者都包含对另一个处理者的引用。如果一个对象不能处理该请求，那么它会把相同的请求传给下一个接收者，依此类推。

## 应用场景：

 1、有多个对象可以处理同一个请求，具体哪个对象处理该请求由运行时刻自动确定。 

2、在不明确指定接收者的情况下，向多个对象中的一个提交一个请求。

3、可动态指定一组对象处理请求。

### 生活中场景

工作流中公文的分级审批；票据需要不同级别的领导审批

### 软件中场景

java中Servlet Filter和Spring Interceptor

## 优点：

- 将请求的接收者和处理者解耦，客户端无需知道具体处理者，只针对抽象处理者编程，简化了客户端编程过程，降低系统耦合度；
- 在系统中增加一个新的处理者时，处理者时无须修改原有系统的代码，只需要在客户端重新建链即可，符合开闭原则；
- 给对象分配职责时，职责链模式赋予系统更多灵活性，可以通过在运行时对该链进行动态的增加或修改来增加或改变处理一个请求的职责。

## 缺点：

- 请求没有一个明确的接收者，就不能保证它一定会被处理；请求也可能因职责链没有被正确配置而得不到处理。
- 对于比较长的职责链，请求的处理可能涉及到多个处理对象，其处理过程会很长。
- 建立职责链的工作是在客户端进行，如果建立不当，可能导致循环调用或者调用失败。

# 模式结构

- **Handler（抽象处理者）：** 定义了一个处理请求的接口，一般设计为抽象类，在其中定义了抽象请求处理方法，由具体处理者实现各自的处理方法。因为每一个处理者的下家还是一个处理者，因此在抽象处理者中定义了一个**抽象处理者类型的对象**，作为其对下家的引用。通过该引用，处理者可以连成一条链。
- **ConcreteHandler（具体处理者）：** 抽象处理者的子类，在具体处理者类中实现了抽象处理者中定义的抽象请求处理方法来处理用户请求，不过在处理请求之前需要进行判断，看是否有相应的处理权限，有权限就处理它，没有则将请求通过下家的引用转发给后继者；

![设计模式之职责链模式](\upload\设计模式之职责链模式\设计模式之职责链模式.jpg)



# 代码示例

模拟不同金额票据需要不同级别的领导审批 ，金额0 ~ 10万含：Teamleader可处理，金额10 ~ 20万含：Supervisor可处理，金额20 ~ 50万含：Manager可处理，金额50 ~ 100万含：Boss可处理，金额超过100万，无人处理，模拟缺点：请求没有一个明确的接收者，就不能保证它一定会被处理。

Handler（抽象处理者）：AbstractHandler

ConcreteHandler（具体处理者）：Teamleader、Supervisor、Manager、Boss

请求：Bill



## GitHub

[ChainOfResponsibility](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E8%81%8C%E8%B4%A3%E9%93%BE%E6%A8%A1%E5%BC%8F/ChainOfResponsibility)

## 请求：Bill

```cpp
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
```

## Handler（抽象处理者）

```cpp
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
```

## ConcreteHandler（具体处理者）

```cpp
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
```

## 测试

```cpp
int main() {
    // 请求处理者：张三， 李四， 王五， 赵六
    AbstractHandler *level1, *level2, *level3, *level4;

    level1 = new TeamLeader("张三");
    level2 = new Supervisor("李四");
    level3 = new Manager("王五");
    level4 = new Boss("赵六");
    std::cout << "=============== " << std::endl;

    /// 建立职责链的工作是在客户端进行
    level1->setNextHandler(level2);
    level2->setNextHandler(level3);
    level3->setNextHandler(level4);

    // 创建单据
    Bill *bill1 = new Bill(1, "Bill_1", 8);
    Bill *bill2 = new Bill(2, "Bill_2", 15);
    Bill *bill3 = new Bill(3, "Bill_3", 99);
    Bill *bill4 = new Bill(4, "Bill_4", 44);
    Bill *bill5 = new Bill(5, "Bill_5", 150);
    std::cout << "=============== " << std::endl;
    // 全部先交给 level1 TeamLeader 审批
    level1->handleRequest(bill1);
    std::cout << "=============== " << std::endl;
    level1->handleRequest(bill2);
    std::cout << "=============== " << std::endl;
    level1->handleRequest(bill3);
    std::cout << "=============== " << std::endl;
    level1->handleRequest(bill4);
    std::cout << "=============== " << std::endl;
    level1->handleRequest(bill5);
    std::cout << "=============== " << std::endl;


    delete level1;delete level2;delete level3;delete level4;
    delete bill1;delete bill2;delete bill3;delete bill4;delete bill5;

    return 0;

}
```



## 输出

![image-20210104213301198](\upload\设计模式之职责链模式\A_设计模式之职责链模式.png)





*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

