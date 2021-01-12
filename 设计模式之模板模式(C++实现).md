更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

[TOC]

# 介绍



## 意图：

**模板方法模式(Template Method Pattern)：**  定义一个操作中算法的框架，而将一些步骤延迟到子类中。模板方法模式使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。

## 解决问题：

解决复用和扩展两个问题

## 实现概述：

 模板方法模式是一种**基于继承的代码复用技术**

## 应用场景：

- 提取算法的框架流程定义在基类中，将可变的行为留给子类来实现
- 提取公共行为并集中到一个公共父类以避免代码重复；
- 通过子类来决定父类算法中某个步骤是否执行，实现子类对父类的反向控制

## 优点：

- 在基类中定义算法的框架，并声明一些流程方法，由具体派生类实现细节，派生类中的实现并不会影响基类定义的算法的框架流程；
- 基类中的公共行为，有利于代码复用；
- 派生类可以覆盖基类的方法，重新实现某些方法，具有灵活性；
- 可以很方便的扩展和更换派生类而不影响基类和其他派生类，**符合开闭原则和单一职责原则**。

## 缺点：

- 模板方法模式要为每一个不同的基本方法提供一个派生类，如果这种基本方法很多，采用模版模式就会导致类的个数很多，系统更加庞大。

# 模式结构

## 角色

- **AbstractClass（抽象类）**：定义或声明了一系列基本操作method，这些操作可以是具体也可以是抽象的，每一个操作都对应算法的一个步骤，在其派生类(子类)中可以重定义。抽象类中定义一个用于定义一个算法的流程框架的方法。
- **ConcreteClass（派生类）**：抽象类的子类，用于实现在父类中声明的抽象基本操作以完成子类特定算法的步骤，也可以覆盖在父类中已经实现的具体基本操作。

## 类图

![设计模式之模板模式](\upload\设计模式之模板模式\设计模式之模板模式.jpg)



# 代码示例

模拟网购，不管是在哪个平台其流程大体为：选商品->加购物车->付款

AbstractClass（抽象类）：OnlineMall

ConcreteClass（派生类）： TaoBao 、JingDong 

## GitHub

[TemplateMethodPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E6%A8%A1%E6%9D%BF%E6%A8%A1%E5%BC%8F/TemplateMethodPattern)

## AbstractClass（抽象类）

```cpp
/// AbstractClass（抽象类）：OnlineMall
class OnlineMall {
public:
    virtual ~OnlineMall() = default;

    // 算法的流程框架
    void shopping(){ /// 流程大体为：选商品->加购物车->付款
        selectProduct();
        addShoppingCart();
        payment();
    }

protected:
    virtual void selectProduct() = 0; /// 选商品
    virtual void addShoppingCart() = 0; /// 加购物车
    virtual void payment() = 0;  /// 付款

    OnlineMall() = default;
};
```



## ConcreteClass（派生类）

```cpp
/// ConcreteClass（派生类）： TaoBao 、JingDong
class TaoBao : public OnlineMall{
public:
    TaoBao() {
        std::cout << "TaoBao Hello" << std::endl;
    }

    ~TaoBao() override {
        std::cout << "TaoBao Bye" << std::endl;
    }

private:
    void selectProduct() override {
        std::cout << "在 TaoBao 选商品" << std::endl;
    }

    void addShoppingCart() override {
        std::cout << "将商品加入 TaoBao 购物车" << std::endl;
    }

    void payment() override {
        std::cout << "支付 TaoBao 购物车待付款给" << std::endl;
    }
};

class JingDong : public OnlineMall{
public:
    JingDong() {
        std::cout << "JingDong Hello" << std::endl;
    }

    ~JingDong() override {
        std::cout << "JingDong Bye" << std::endl;
    }

private:
    void selectProduct() override {
        std::cout << "在 JingDong 选商品" << std::endl;
    }

    void addShoppingCart() override {
        std::cout << "将商品加入 JingDong 购物车" << std::endl;
    }

    void payment() override {
        std::cout << "支付 JingDong 购物车待付款给" << std::endl;
    }
};
```



## 测试

```cpp
int main() {

    OnlineMall* shopTaoBao= new TaoBao();
    shopTaoBao->shopping();
    delete shopTaoBao;

    OnlineMall* shopJingDong = new JingDong();
    shopJingDong->shopping();
    delete shopJingDong;

    return 0;
}
````



## 输出

![image-20210112151916006](\upload\设计模式之模板模式\A_设计模式之模板模式.png)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

