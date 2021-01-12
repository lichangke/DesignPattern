更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

[TOC]

# 介绍

访问者模式包含**访问者**和**被访问元素**两个主要组成部分，这些被访问的元素通常具有不同的类型，且不同的访问者可以对它们进行不同的访问操作。

## 意图：

**访问者模式(Visitor Pattern):** 提供一个作用于某对象结构中的各元素的操作表示，它使我们可以在不改变各元素的类的前提下定义作用于这些元素的新操作。

## 解决问题：

将**对象与操作**解耦，将业务操作抽离出来，定义在独立细分的**访问者类**中

## 实现概述：

访问者模式中对象结构存储了**不同类型的元素对象**，让不同访问者访问。

访问者模式包括两个层次结构，一个是**访问者层次结构**，提供了**抽象访问者**和**具体访问者**（继承），一个是**元素层次结构**，提供了**抽象元素**和**具体元素**（继承）。相同访问者可以采用不同的方法访问不同的元素（函数重载），同样的相同元素可以被不同的访问者采用不同的方式访问。

## 要点：

双重分派机制的采用

## 应用场景：

系统中存在一个较为复杂的对象结构，且不同访问者对其所采取的操作也不相同时，可以考虑使用访问者模式进行设计。对象结构中对象对应的类很少改变，但经常需要在此对象结构上定义新的操作。

## 优点：

- 增加新的访问者很方便，即增加一个新的具体访问者类，定义新的访问方式，无需修改原有代码；
- 被访问元素集中在一个访问者对象中，类的职责更清晰，利于对象结构中元素对象的复用；

## 缺点：

- 增加新的元素类很困难，增加新的元素时，需要修改抽象访问者代码，在抽象访问者类中需要增加一个对新增的元素方法的声明；并在具体访问者中也要添加相应代码，不符合开闭原则；
- 访问者模式破坏了对象的封装性，它要求访问者对象有能力访问并调用每一个元素对象的操作，那么元素对象必然要暴露自己的内部操作和状态，否则访问者无法访问。

# 模式结构

## 角色

- **Visitor（抽象访问者）：**  为对象结构中每一个具体元素类ConcreteElement声明一个访问操作，通过名称或参数类型这个方法知道需要访问的**具体元素的类型**，**具体访问者**实现这些操作方法，定义对这些元素的访问操作（重载）。
- **ConcreteVisitor（具体访问者）：** 实现了抽象访问者声明的操作，每一个操作用于访问对象结构中一种类型的元素。
- **Element（抽象元素）：** 一般是抽象类或者接口，它定义一个accept()方法，该方法通常以一个**抽象访问者**作为参数。
- **ConcreteElement（具体元素）：** 针对具体被访问的元素，实现accept()方法；
- **ObjectStructure（对象结构）：** 元素的集合，提供了遍历对象结构中所有元素的方法。对象结构存储了不同类型的元素对象，以供不同的访问者访问。

## 类图





# 代码示例

采用访问者模式，模拟顾客 Customer 去买商品，比如 买肉类，猪肉 Pork 和 水果， 苹果 Apple 等，并到收银员 Cashier 那里付款。Customer 关心所买商品，Cashier 关心价格

Visitor（抽象访问者）： Visitor

ConcreteVisitor（具体访问者）： Customer 、 Cashier 

Element（抽象元素）： Element

ConcreteElement（具体元素）： Pork  、 Apple 

ObjectStructure（对象结构）：ShoppingCart(类中有Element的容器存储具体ConcreteElement， Pork  和 Apple )



## GitHub

[VisitorPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E8%AE%BF%E9%97%AE%E8%80%85%E6%A8%A1%E5%BC%8F/VisitorPattern)

## Visitor（抽象访问者）

```cpp
/// Visitor（抽象访问者）： Visitor
class Visitor {
public:
    virtual ~Visitor() = default;
    // 声明一组访问方法
    virtual void visit(Apple* apple) = 0;
    virtual void visit(Pork* pork) = 0;

protected:
    Visitor()= default;
};
```



## ConcreteVisitor（具体访问者）

```cpp
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
```



## Element（抽象元素）

```cpp
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
```



## ConcreteElement（具体元素）

```cpp
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

/// 放在 Visitor 类后
void Apple::accept(Visitor* visitor) {
    visitor->visit(this);
}
void Pork::accept(Visitor* visitor) {
    visitor->visit(this);
}
```



## ObjectStructure（对象结构）

```cpp
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
```



## 测试

```cpp
int main() {

    Apple *apple1 = new Apple("红富士苹果", 7);
    Apple *apple2 = new Apple("烟台苹果", 5);
    Pork *pork1 = new Pork("里脊肉", 45);
    Pork *pork2 = new Pork("五花肉", 28);

    auto* cashier = new Cashier();
    auto* customer = new Customer("张三");
    customer->setNum(apple1, 3);
    customer->setNum(apple2, 4);
    customer->setNum(pork1, 1);
    customer->setNum(pork2, 2);

    auto* shoppingCart = new ShoppingCart();
    std::cout << "===购物车添加商品===" << std::endl;
    shoppingCart->addElement(apple1);
    shoppingCart->addElement(apple2);
    shoppingCart->addElement(pork1);
    shoppingCart->addElement(pork2);
    std::cout << "===顾客选择的商品===" << std::endl;
    shoppingCart->accept(customer);
    std::cout << "===收银员计算的价格===" << std::endl;
    shoppingCart->accept(cashier);
    std::cout << "========" << std::endl;

    delete apple1;delete apple2;
    delete pork1;delete pork2;
    delete cashier;delete customer;
    delete shoppingCart;
    return 0;
}
```



## 输出

![image-20210112213305578](\upload\设计模式之访问者模式\A_设计模式之访问者模式.png)

*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

