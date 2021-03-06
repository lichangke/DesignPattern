更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍

工厂方法模式中考虑的是一类产品的生产，如畜牧场只养动物、电视机厂只生产电视机、计算机软件学院只培养计算机软件专业的学生等。一个工厂只生产一类产品，可能会导致系统中存在大量的工厂类，势必会增加系统的开销。此时，我们可以考虑将一些相关的产品组成一个“产品族”，由同一个工厂来统一生产，如一个电器工厂，它可以生产电视机、电冰箱、空调等多种电器，而不是只生产某一种电器。

引入两个概念：

 (1) **产品等级结构**：产品等级结构即产品的继承结构，如一个抽象类是电视机，其子类有海尔电视机、海信电视机、TCL电视机，则抽象电视机与具体品牌的电视机之间构成了一个产品等级结构，抽象电视机是父类，而具体品牌的电视机是其子类。

  (2) **产品族**：在抽象工厂模式中，产品族是指由同一个工厂生产的，位于不同产品等级结构中的一组产品，如海尔电器工厂生产的海尔电视机、海尔电冰箱，海尔电视机位于电视机产品等级结构中，海尔电冰箱位于电冰箱产品等级结构中，海尔电视机、海尔电冰箱构成了一个产品族。

![电器工厂的产品等级与产品族](\upload\设计模式之抽象工厂模式\A_设计模式之抽象工厂模式.gif)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201225230637563.gif)





## 意图：

**抽象工厂模式(Abstract Factory Pattern)**：提供一个创建一系列相关或相互依赖对象的接口，而无须指定它们具体的类。抽象工厂模式又称为Kit模式，它是一种对象创建型模式。抽象工厂模式中的具体工厂不只是创建一种产品，它负责创建一族产品。

## 解决问题：

主要解决接口选择的问题。

## 实现概述：

## 要点：

抽象工厂模式为创建一组对象提供了一种解决方案。与工厂方法模式相比，抽象工厂模式中的具体工厂不只是创建一种产品，它负责创建一族产品。

## 应用场景：

 在以下情况下可以考虑使用抽象工厂模式：

 (1) 一个系统不应当依赖于产品类实例如何被创建、组合和表达的细节，用户无须关心对象的创建过程，将对象的创建和使用解耦。
 (2) 系统中有多于一个的产品族，而每次只使用其中某一产品族。
 (3) 属于同一个产品族的产品将在一起使用，这一约束必须在系统的设计中体现出来。同一个产品族中的产品可以是没有任何关系的对象，但是它们都具有一些共同的约束。
 (4) 产品等级结构稳定，设计完成之后，不会向系统中增加新的产品等级结构或者删除已有的产品等级结构。

### 生活中场景

比如如海尔电器工厂既生产海尔电视机也生产海尔电冰箱

### 软件中场景

QQ 换皮肤，一整套一起换

## 优点：

1. 抽象工厂模式隔离了具体类的生成，使得客户并不需要知道什么被创建，这使得更换一个具体工厂就变得相对容易
2. 当一个产品族中的多个对象被设计成一起工作时，它能够保证客户端始终只使用同一个产品族中的对象。
3.  增加新的产品族很方便，无须修改已有系统，符合“开闭原则”。

## 缺点：

增加新的产品等级结构麻烦，需要对原有系统进行较大的修改，甚至需要修改抽象层代码，这显然会带来较大的不便，违背了“开闭原则”。



# 模式结构

 ● **抽象工厂（AbstractFactory）**：它声明了一组用于创建一族产品的方法，每一个方法对应一种产品。
 ● **具体工厂（ConcreteFactory）**：它实现了在抽象工厂中声明的创建产品的方法，生成一组具体产品，这些产品构成了一个产品族，每一个产品都位于某个产品等级结构中。
 ● **抽象产品（AbstractProduct）**：它为每种产品声明接口，在抽象产品中声明了产品所具有的业务方法。
 ● **具体产品（ConcreteProduct）**：它定义具体工厂生产的具体产品对象，实现抽象产品接口中声明的业务方法。在抽象工厂中声明了多个工厂方法，用于创建不同类型的产品

```cpp
//抽象产品类A
class AbstractProductA
{
public:
	//抽象方法：
};
 
//具体产品类A
class ConcreteProductA :public AbstractProductA
{
public:
	//具体实现方法
};
//抽象产品类B
class AbstractProductB
{
public:
	//抽象方法：
};
 
//具体产品类B
class ConcreteProductB :public AbstractProductB
{
public:
	//具体实现方法
};
 
//抽象工厂类
class AbstractFactory 
{
public:
	//抽象方法生产产品A：
    virtual AbstractProductA * createProductA() = 0;
    virtual AbstractProductB * createProductB() = 0;
};
 
//具体工厂类A
class ConcreteFactoryA :public AbstractFactory
{
public:
	//具体工厂生产具体产品
};
//具体工厂类B
class ConcreteFactoryB :public AbstractFactory
{
public:
	//具体工厂生产具体产品
};
```



![设计模式之抽象工厂模式](\upload\设计模式之抽象工厂模式\设计模式之抽象工厂模式.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201225230713688.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



# 代码示例

## GitHub

[AbstractFactory](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E6%8A%BD%E8%B1%A1%E5%B7%A5%E5%8E%82%E6%A8%A1%E5%BC%8F/AbstractFactory)

## 定义抽象产品类

```cpp
///定义抽象产品类
class AbstractPhoneProduct
{
public:
    virtual ~AbstractPhoneProduct() = default;
    //抽象方法：
    virtual void productName() = 0;
    virtual void productIntroduction() = 0;
protected:
    AbstractPhoneProduct()= default;

};
///定义抽象产品类
class AbstractTVProduct
{
public:
    virtual ~AbstractTVProduct() = default;
    //抽象方法：
    virtual void productName() = 0;
    virtual void productIntroduction() = 0;
protected:
    AbstractTVProduct()= default;

};

```



## 定义具体产品类

```cpp
///2个具体产品类
///具体产品类 HWPhone
class HWPhone :public AbstractPhoneProduct
{
public:
    HWPhone() = default;
    ~HWPhone() override {
        std::cout << "HWPhone Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a HWPhone" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for HWPhone" << std::endl;
    }
};

///具体产品类 MIPhone
class MIPhone :public AbstractPhoneProduct
{
public:
    MIPhone() = default;
    ~MIPhone() override {
        std::cout << "MIPhone Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a MIPhone" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for MIPhone" << std::endl;
    }
};

///2个具体产品类
///具体产品类 HWTV
class HWTV :public AbstractTVProduct
{
public:
    HWTV() = default;
    ~HWTV() override {
        std::cout << "HWTV Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a HWTV" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for HWTV" << std::endl;
    }
};

///具体产品类 MITV
class MITV :public AbstractTVProduct
{
public:
    MITV() = default;
    ~MITV() override {
        std::cout << "MITV Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a MITV" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for MITV" << std::endl;
    }
};
```



## 定义抽象工厂类

```cpp
/// 定义抽象工厂类
class AbstractFactory
{
public:
    virtual ~AbstractFactory() = default;
    virtual AbstractPhoneProduct * createPhone() = 0;
    virtual AbstractTVProduct * createTV() = 0;
protected:
    AbstractFactory() = default;
};
```



## 定义具体工厂类

```cpp

///两个具体工厂类
///具体工厂类  生产多个产品
class HWFactory : public AbstractFactory
{
public:
    HWFactory() = default;
    ~HWFactory() override {
        std::cout << "HWFactory Bye" << std::endl;
    };
    AbstractPhoneProduct *createPhone() override{
        return  new HWPhone();
    }
    AbstractTVProduct *createTV() override{
        return  new HWTV();
    }
};

///具体工厂类  生产多个产品
class MIFactory : public AbstractFactory
{
public:
    MIFactory() = default;
    ~MIFactory() override {
        std::cout << "MIFactory Bye" << std::endl;
    };
    AbstractPhoneProduct *createPhone() override{
        return  new MIPhone();
    }
    AbstractTVProduct *createTV() override{
        return  new MITV();
    }
};

```



## 测试

```cpp

int main() {

    std::cout << "抽象工厂模式" << std::endl;


    //定义工厂类对象和产品类对象
    AbstractPhoneProduct *phone = nullptr;
    AbstractTVProduct *tv = nullptr;
    AbstractFactory *factory = nullptr;

    factory = new HWFactory();
    phone = factory->createPhone();
    phone->productName();
    tv = factory->createTV();
    tv->productIntroduction();
    delete factory;
    delete phone;
    delete tv;

    factory = new MIFactory();
    phone = factory->createPhone();
    phone->productName();
    tv = factory->createTV();
    tv->productIntroduction();
    delete factory;
    delete phone;
    delete tv;


    getchar();
    return 0;
}

```



## 输出

![image-20201225154320853](\upload\设计模式之抽象工厂模式\B_设计模式之抽象工厂模式.png)



![在这里插入图片描述](https://img-blog.csdnimg.cn/20201225230734502.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

