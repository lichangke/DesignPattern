//
// Created by leacock on 2021/1/12.
//

#ifndef VISITORPATTERN_VISITORPATTERN_H
#define VISITORPATTERN_VISITORPATTERN_H

#include <iostream>
#include <vector>

class Visitor;

/// Element（抽象元素）： Element
class Element {
public:
    virtual ~Element() = default;
    virtual void accept(Visitor* visitor) = 0;

    int getPrice(){
        return price;
    }

    int getNum(){
        return num;
    }

    std::string getName(){
        return name;
    }

    void setPrice(int iPrice){
        price = iPrice;
    }
    void setNum(int iNum){
        num = iNum;
    }
    void setName(const std::string &iName){
        name = iName;
    }

protected:
    Element() {
        price = 0;
        num = 0;
    }
    int price;
    int num;
    std::string name;
};

/// ConcreteElement（具体元素）： Pork  、 Apple
// 具体元素：Apple
class Apple :public Element {
public:
    Apple(const std::string &name, int price) {
        setPrice(price);
        setNum(0);
        setName(name);
        std::cout << "Apple Hello,name = " << name << std::endl;
    }
    ~Apple() override {
        std::cout << "Apple Bye,name = " << name << std::endl;
    }
    void accept(Visitor*) override;
};
// 具体元素：Apple
class Pork :public Element {
public:
    Pork(const std::string &name, int price) {
        setPrice(price);
        setNum(0);
        setName(name);
        std::cout << "Pork Hello,name = " << name << std::endl;
    }
    ~Pork() override {
        std::cout << "Pork Bye,name = " << name << std::endl;
    }
    void accept(Visitor*) override;
};

/// Visitor（抽象访问者）： Visitor
class Visitor {
public:
    virtual ~Visitor() = default;
    // 声明一组访问方法
    virtual void visit(Apple*) = 0;
    virtual void visit(Pork*) = 0;

protected:
    Visitor()= default;
};

/// ConcreteVisitor（具体访问者）： Customer 、 Cashier
// 具体访问者：顾客
class Customer :public Visitor
{
public:
    explicit Customer(const std::string &iName) {
        name = iName;
        std::cout << "Customer Hello,name = " << name << std::endl;
    }
    ~Customer() override {
        std::cout << "Customer Bye,name = " << name << std::endl;
    };
    void setNum(Apple*apple , int num) {
        apple->setNum(num);
    }
    void setNum(Pork* pork, int num) {
        pork->setNum(num);
    }
    void visit(Apple* apple) override {
        std::cout << apple->getName() << "\t 单价: " << apple->getPrice() << "元/kg" << std::endl;
    }
    void visit(Pork* pork) override {
        std::cout << pork->getName() << "\t 单价: " << pork->getPrice() << "元/kg" << std::endl;
    }
private:
    std::string name;
};

class Cashier :public Visitor
{
public:
    Cashier() {
        std::cout << "Cashier Hello" << std::endl;
    }
    ~Cashier() override {
        std::cout << "Cashier Bye" << std::endl;
    };

    void visit(Apple* apple) override{
        std::string name = apple->getName();
        int price = apple->getPrice();
        int num = apple->getNum();
        int total = price*num;
        std::cout << name << "\t 总价: " << total << "元" << std::endl;
    }

    void visit(Pork* pork) override{
        std::string name = pork->getName();
        int price = pork->getPrice();
        int num = pork->getNum();
        int total = price*num;
        std::cout << name << "\t 总价: " << total << "元" << std::endl;
    }
};

/// ObjectStructure（对象结构）：ShoppingCart(类中有Element的容器存储具体ConcreteElement， Pork  和 Apple )
class ShoppingCart
{
public:
    ShoppingCart(){
        std::cout << "ShoppingCart Hello" << std::endl;
    }
    ~ShoppingCart(){
        std::cout << "ShoppingCart Bye" << std::endl;
    }

    void addElement(Element* element){
        std::cout <<"商品：" << element->getName() << "\t 数量： " << element->getNum() << " \t 加入购物车！" << std::endl;
        elementList.push_back(element);
    }
    void accept(Visitor* visitor){
        for (auto & element : elementList){
            element->accept(visitor);
        }
    }
private:
    std::vector<Element*>elementList;
};

/// 放在 Visitor 类后
void Apple::accept(Visitor* visitor) {
    visitor->visit(this);
}
void Pork::accept(Visitor* visitor) {
    visitor->visit(this);
}

#endif //VISITORPATTERN_VISITORPATTERN_H
