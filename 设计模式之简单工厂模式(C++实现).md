更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍

按实际业务场景划分，工厂模式有 3 种不同的实现方式，分别是`简单工厂模式`、`工厂方法模式`和`抽象工厂模式`。

把被创建的对象称为“产品”，把创建产品的对象称为“工厂”。如果要创建的产品不多，只要一个工厂类就可以完成，这种模式叫**简单工厂模式**。

在简单工厂模式中创建实例的方法通常为静态（static）方法，因此**简单工厂模式（Simple Factory Pattern）又叫作静态工厂方法模式（Static Factory Method Pattern）。**



## 意图：

 **简单工厂模式(Simple Factory Pattern)**：定义一个工厂类，它可以根据参数的不同返回不同类的实例，被创建的实例通常都具有共同的父类。

## 解决问题：

主要解决接口选择的问题。

## 实现概述：

- 将需要创建的各种不同对象的相关代码封装到不同的类中，这些类称为**具体产品类**
- 将它们公共的代码进行抽象和提取后封装在一个**抽象产品类**，每一个具体产品类都是抽象产品类的子类
- 提供一个**工厂类**用于创建各种产品，工厂类中提供一个创建产品的工厂方法，该方法可以根据所传入的参数不同创建不同的具体产品对象

## 要点：

当你需要什么，只需要传入一个正确的参数，就可以获取你所需要的对象，而无须知道其创建细节。

## 应用场景：

在以下情况下可以考虑使用简单工厂模式：

​    (1) 工厂类负责创建的对象比较少，由于创建的对象较少，不会造成工厂方法中的业务逻辑太过复杂。

​    (2) 客户端只知道传入工厂类的参数，对于如何创建对象并不关心。

### 生活中场景

不同工厂生产不同的产品。比如不同的球类工厂生产不同的球类。

### 软件中场景

 1、日志记录器：记录可能记录到本地硬盘、系统事件、远程服务器等，用户可以选择记录日志到什么地方。 

2、数据库访问，当用户不知道最后系统采用哪一类数据库，以及数据库可能有变化时。

## 优点：

1. 工厂类包含必要的逻辑判断，可以决定在什么时候创建哪一个产品的实例。
2. 客户端无需知道所创建具体产品的类名，只需知道参数即可。

## 缺点：

1. 简单工厂模式的工厂类单一，负责所有产品的创建，职责过重，一旦异常，整个系统将受影响。且工厂类代码会非常臃肿，违背高聚合原则。
2. 系统扩展困难，一旦增加新产品不得不修改工厂逻辑，在产品类型较多时，可能造成逻辑过于复杂
3. 简单工厂模式使用了 static 工厂方法，造成工厂角色无法形成基于继承的等级结构。

## 模式结构

- **抽象产品（Product）**：是简单工厂创建的所有对象的父类，负责描述所有实例共有的公共接口。
- **具体产品（ConcreteProduct）**：抽象产品的派生类，包含具体产品特有的实现方法，是简单工厂模式的创建目标。
- **简单工厂（SimpleFactory）**：根据客户提供的具体产品参数，创建具体产品实例



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
 
class SimpleFactory
{
public:
	AbstractProduct createProduct(string productName)
	{
		AbstractProduct pro = NULL;
		if (productName == "ProductA"){
			pro = new ProductA();
		}
		else if (productName == "ProductB"){
			pro = new ProductB();
		}
		...
	}
};
```



![设计模式之简单工厂模式](\upload\设计模式之简单工厂模式\设计模式之简单工厂模式.jpg)



![在这里插入图片描述](https://img-blog.csdnimg.cn/20201225225736937.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



# 代码示例

不同的球类工厂生产不同的球类。

### GitHub

[**SimpleFactory**](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E7%AE%80%E5%8D%95%E5%B7%A5%E5%8E%82%E6%A8%A1%E5%BC%8F/SimpleFactory)

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
//三个具体产品类
//具体产品类Basketball
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

//具体产品类Football
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

//具体产品类Volleyball
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

### 定义工厂类

```cpp
/// 定义工厂类和工厂方法
class SimpleFactory
{
public:
    static AbstractBallProduct *getProduct(const std::string& productName)
    {
        AbstractBallProduct *pro = nullptr;
        if (productName == "Basketball"){
            pro = new Basketball();
        }
        else if (productName == "Football"){
            pro = new Football();
        }
        else if (productName == "Volleyball"){
            pro = new Volleyball();
        }
        return pro;
    }
};
```

### 测试

```cpp
int main() {
    std::cout << "简单工厂模式" << std::endl;
    //定义工厂类对象
    AbstractBallProduct *product = nullptr;
    product = SimpleFactory::getProduct("Basketball");
    product->productName();
    delete product;

    product = SimpleFactory::getProduct("Football");
    product->productIntroduction();
    delete product;

    product = SimpleFactory::getProduct("Volleyball");
    product->productIntroduction();
    delete product;
    getchar();
    return 0;
}
```

### 输出

![image-20201224165935326](\upload\设计模式之简单工厂模式\A_设计模式之简单工厂模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201225225803313.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

