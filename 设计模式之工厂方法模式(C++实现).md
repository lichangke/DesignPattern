更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍

简单工厂模式中，SimpleFactory类中有一组 if 分支判断逻辑，由于这个分支判断逻辑**当系统中需要引入新产品时，由于静态工厂方法通过所传入参数的不同来创建不同的产品，这必定要修改工厂类的源代码，将违背“开闭原则”**。

是不是应该用多态或其他设计模式来替代呢？实际上，如果 if 分支并不是很多，代码中有 if 分支也是完全可以接受的。应用多态或设计模式来替代 if 分支判断逻辑，也并不是没有任何缺点的，它虽然提高了代码的扩展性，更加符合开闭原则，但也增加了类的个数，牺牲了代码的可读性。

如果我们非得要将 if 分支逻辑去掉，那该怎么办呢？比较经典处理方法就是利用多态。在SimpleFactory之上再抽象一层。

`工厂方法模式`是对简单工厂模式的进一步抽象化，其好处是可以使系统在不修改原来代码的情况下引进新的产品，即满足开闭原则。

## 意图：

**工厂方法模式(Factory Method Pattern)：**定义一个用于创建对象的接口，让子类决定将哪一个类实例化。工厂方法模式让一个类的实例化延迟到其子类。工厂方法模式又简称为工厂模式(Factory Pattern)，又可称作虚拟构造器模式(Virtual Constructor Pattern)或多态工厂模式(Polymorphic Factory Pattern)。工厂方法模式是一种类创建型模式。

## 实现概述：

工厂方法模式提供一个抽象工厂接口来声明抽象工厂方法，而由其子类来具体实现工厂方法，创建具体的产品对象。

## 要点：

基于工厂角色和产品角色的多态性设计是工厂方法模式的关键。不再提供一个统一的工厂类来创建所有的产品对象，而是针对不同的产品提供不同的工厂，系统提供一个与产品等级结构对应的工厂等级结构。

## 应用场景：

在以下情况下可以考虑使用工厂方法模式：

​    (1) 客户端不知道它所需要的对象的类。在工厂方法模式中，客户端不需要知道具体产品类的类名，只需要知道所对应的工厂即可，具体的产品对象由具体工厂类创建，可将具体工厂类的类名存储在配置文件或数据库中。

​    (2) 抽象工厂类通过其子类来指定创建哪个对象。在工厂方法模式中，对于抽象工厂类只需要提供一个创建产品的接口，而由其子类来确定具体要创建的对象，利用面向对象的多态性和里氏代换原则，在程序运行时，子类对象将覆盖父类对象，从而使得系统更容易扩展。



## 优点：

- 用户只需要知道具体工厂的名称就可得到所要的产品，无须知道产品的具体创建过程。
- 灵活性增强，对于新产品的创建，只需多写一个相应的工厂类。
- 典型的解耦框架。高层模块只需要知道产品的抽象类，无须关心其他实现类，满足迪米特法则、依赖倒置原则和里氏替换原则。

## 缺点：

- 类的个数容易过多，增加复杂度
- 增加了系统的抽象性和理解难度
- 抽象产品只能生产一种产品，此弊端可使用抽象工厂模式解决。



# 模式结构



- **抽象工厂（AbstractFactory）**：提供了创建产品的接口，调用者通过它访问具体工厂的工厂方法 newProduct() 来创建产品。
- **具体工厂（ConcreteFactory）**：主要是实现抽象工厂中的抽象方法，完成具体产品的创建。
- **抽象产品（Product）**：定义了产品的规范，描述了产品的主要特性和功能。
- **具体产品（ConcreteProduct）**：实现了抽象产品角色所定义的接口，由具体工厂来创建，它同具体工厂之间一一对应。

```cpp
//抽象产品类
class AbstractProduct
{
public:
	//抽象方法：
};
 
//具体产品类
class ConcreteProduct :public AbstractProduct
{
public:
	//具体实现方法
};
 
//抽象工厂类
class AbstractFactory 
{
public:
	//抽象方法生产产品：
    virtual AbstractProduct * createProduct() = 0;
};
 
//具体工厂类
class ConcreteFactory :public AbstractFactory
{
public:
	//具体工厂生产具体产品
    
};
```



![01_工厂方法](/upload\设计模式之工厂方法模式\设计模式之工厂方法模式.jpg)



![在这里插入图片描述](https://img-blog.csdnimg.cn/2020122523041080.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



# 代码示例

不同的球类工厂生产不同的球类。

### GitHub

[**FactoryMethod**](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E5%B7%A5%E5%8E%82%E6%96%B9%E6%B3%95%E6%A8%A1%E5%BC%8F/FactoryMethod)

### 定义抽象产品类

```cpp
///定义抽象产品类
class AbstractBallProduct
{
public:
    virtual ~AbstractBallProduct() = default;
    //抽象方法：
    virtual void productName() = 0;
    virtual void productIntroduction() = 0;
protected:
    AbstractBallProduct()= default;

};
```



### 定义具体产品类

```cpp
///三个具体产品类
///具体产品类Basketball
class Basketball :public AbstractBallProduct
{
public:
    Basketball() = default;
    ~Basketball() override {
        std::cout << "Basketball Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Basketball" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Basketball" << std::endl;
    }
};

///具体产品类Football
class Football :public AbstractBallProduct
{
public:
    Football() = default;
    ~Football() override {
        std::cout << "Football Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Football" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Football" << std::endl;
    }
};

///具体产品类Volleyball
class Volleyball :public AbstractBallProduct
{
public:
    Volleyball() = default;
    ~Volleyball() override {
        std::cout << "Volleyball Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Volleyball" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Volleyball" << std::endl;
    }
};
```



### 定义抽象工厂类

```cpp
/// 定义抽象工厂类
class AbstractFactory
{
public:
    virtual ~AbstractFactory() = default;
    virtual AbstractBallProduct * createProduct() = 0;
protected:
    AbstractFactory() = default;
};
```



### 定义具体工厂类

```cpp
///三个具体工厂类
///具体工厂类  只生产单一产品
class BasketballFactory : public AbstractFactory
{
public:
    BasketballFactory() = default;
    ~BasketballFactory() override {
        std::cout << "BasketballFactory Bye" << std::endl;
    };
    AbstractBallProduct *createProduct() override{
        return  new Basketball();
    }
};

///具体工厂类  只生产单一产品
class FootballFactory : public AbstractFactory
{
public:
    FootballFactory() = default;
    ~FootballFactory() override {
        std::cout << "FootballFactory Bye" << std::endl;
    };
    AbstractBallProduct *createProduct() override{
        return  new Football();
    }
};
///具体工厂类  只生产单一产品
class VolleyballFactory : public AbstractFactory
{
public:
    VolleyballFactory() = default;
    ~VolleyballFactory() override {
        std::cout << "VolleyballFactory Bye" << std::endl;
    };
    AbstractBallProduct *createProduct() override{
        return  new Volleyball();
    }
};
```

### 测试

```cpp
int main() {

    std::cout << "工厂方法模式" << std::endl;
    //定义工厂类对象和产品类对象
    AbstractBallProduct *product = nullptr;
    AbstractFactory *factory = nullptr;

    factory = new BasketballFactory();
    product = factory->createProduct();
    product->productName();
    delete factory;
    delete product;


    factory = new FootballFactory();
    product = factory->createProduct();
    product->productIntroduction();
    delete factory;
    delete product;

    factory = new VolleyballFactory();
    product = factory->createProduct();
    product->productIntroduction();
    delete factory;
    delete product;

    getchar();
    return 0;
}

```

### 输出

![image-20201224174952734](/upload\设计模式之工厂方法模式\A_设计模式之工厂方法模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201225230420321.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*