更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍

装饰器模式（Decorator Pattern）允许向一个现有的对象添加新的功能，同时又不改变其结构。这种类型的设计模式属于结构型模式，它是作为现有的类的一个包装。

## 意图：

**装饰模式(Decorator Pattern)：** 动态地给一个对象增加一些额外的职责，就增加对象功能来说，装饰模式比生成子类实现更为灵活。装饰模式是一种对象结构型模式。

## 解决问题：

通常情况下，扩展一个类的功能会使用继承方式来实现。但继承具有静态特征，耦合度高，并且随着扩展功能的增多，子类会很膨胀。如果使用组合关系来创建一个包装对象（即装饰对象）来包裹真实对象，并在保持真实对象的类结构不变的前提下，为其提供额外的功能，这就是装饰模式的目标。

## 实现概述：

使用组合关系来创建一个包装对象（即装饰对象）来包裹真实对象，并在保持真实对象的类结构不变的前提下，为其提供额外的功能。

## 要点：

装饰模式的核心在于**抽象装饰类**的设计，抽象装饰类(装饰器类)和原始类继承同样的父类，这样可以对原始类“嵌套”多个装饰器类。抽象装饰类(装饰器类)是对功能的增强，这也是装饰器模式应用场景的一个重要特点。并且抽象装饰类**维持一个对抽象构件对象的引用**component，**抽象装饰类**可以通过构造函数或Setter方法**注入一个抽象构件类型的对象**。

## 应用场景：

(1) 在不影响其他对象的情况下，给单个对象动态扩展职责；

(2) 不适宜采用继承的方式进行扩展的时候，可以考虑使用装饰模式。

比如 Java IO类库



## 优点：

(1) 对于扩展一个对象的功能，装饰模式比继承更加灵活性，不会导致类的个数急剧增加。

(2) 可以通过一种动态的方式来扩展一个对象的功能。

(3) 可以对一个对象进行多次装饰，通过使用不同的具体装饰类以及这些装饰类的排列组合进行多次装饰。

(4) 具体构件类与具体装饰类可以独立变化，符合“开闭原则”。

## 缺点：

(1) 装饰模式中会增加很多小的对象，对象的区别主要在于各种装饰的连接方式不同，而并不是职责不同，大量小对象的产生会占用较多的系统资源；

(2) 装饰模式比继承模式更灵活，但也更容易出错，更难于排错。

# 模式结构

- **Component（抽象构件）：** 它是**具体构件**和**抽象装饰类**的**共同父类**，声明了在具体构件中实现的业务方法，使客户端能够以一致的方式处理未被装饰的对象以及装饰之后的对象。

- **ConcreteComponent（具体构件）：** 它是**抽象构件类的子类**，实现了在抽象构件中声明的方法，装饰器就是为它增加额外的功能（方法）。

-  **Decorator（抽象装饰类）：** 它也是**抽象构件类的子类**，用于给具体构件增加功能，但是具体功能在它的子类中实现。它维护一个**指向抽象构件对象的引用**，通过该引用可以调用构件对象的方法，并通过其子类(**具体装饰类**)扩展该方法，以达到装饰的目的。

- **ConcreteDecorator（具体装饰类）：** 它是**抽象装饰类的子类**，负责向构件添加新的功能。每一个具体装饰类都定义了一些新的行为，它可以调用在抽象装饰类中定义的方法，并可以增加新的方法用以扩充对象的行为。



![设计模式之装饰器模式](\upload\设计模式之装饰器模式\设计模式之装饰器模式.jpg)

# 代码示例

今天上班途中在路边的小车车那买了个手抓饼作为早餐，商家价格，基础3元版，基础5元版，加鸡蛋1.5元，加火腿肠1元，加青菜0.5元 等，由于没钱只好买了个基础3元版的╮(╯▽╰)╭。可以使用装饰器模式来表示购买不同组合的手抓饼。

Component（抽象构件）： HandPancake

ConcreteComponent（具体构件）： ConcreteHandPancake

Decorator（抽象装饰类）：Decorator

ConcreteDecorator（具体装饰类）：addEgg ,  addSausage , addVegetable 

## GitHub

[DecoratorPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E8%A3%85%E9%A5%B0%E5%99%A8%E6%A8%A1%E5%BC%8F/DecoratorPattern)

## Component（抽象构件）

```cpp
/// Component（抽象构件）： HandPancake
class HandPancake {
public:
    virtual ~HandPancake() = default;
    virtual std::string offerHandPancake() = 0; // 制作手抓饼
    virtual float calcPrice() = 0; // 计算价格
protected:
    HandPancake() = default;
};
```



## ConcreteComponent（具体构件）

```cpp
enum TYPE {
    Base3 = 3,
    Base5 = 5,
};
/// ConcreteComponent（具体构件）： ConcreteHandPancake
class ConcreteHandPancake : public HandPancake {
public:
    explicit ConcreteHandPancake(TYPE price) {
        std::cout << "ConcreteHandPancake Hello" << std::endl;
        basePrice = price;
    }
    ~ConcreteHandPancake() override {
        std::cout << "ConcreteHandPancake Bye" << std::endl;
    }
    std::string offerHandPancake() override {
        std::stringstream buf;
        buf.precision(2);//覆盖默认精度
        buf.setf(std::ios::fixed);//保留小数位自动补0
        buf << basePrice;
        std::string str;
        str = buf.str();

        return "基础"+ str + "元手抓饼" ;
    }
    float calcPrice() override {
        return basePrice;
    }

private:
    float basePrice;
};
```



## Decorator（抽象装饰类）

```cpp
/// Decorator（抽象装饰类）：Decorator
class Decorator : public HandPancake {
public:
    explicit Decorator(HandPancake *handPancake) {
        this->handPancake = handPancake;
    }
    ~Decorator() override {
        delete handPancake;
    };

    std::string offerHandPancake() override {
        return handPancake->offerHandPancake();
    }
    float calcPrice() override {
        return handPancake->calcPrice();
    }

private:
    HandPancake *handPancake; // 维持一个对抽象构件对象的引用
};
```





## ConcreteDecorator（具体装饰类）

```cpp
/// ConcreteDecorator（具体装饰类）：addEgg ,  addSausage , addVegetable ,
class addEgg : public Decorator {
public:
    explicit addEgg(HandPancake *handPancake): Decorator(handPancake) {
        std::cout << "addEgg Hello" << std::endl;
    };
    ~addEgg() override {
        std::cout << "addEgg Bye" << std::endl;
    }
    std::string offerHandPancake() override {
        return Decorator::offerHandPancake() + ",加了鸡蛋";
    }
    float calcPrice() override {
        return Decorator::calcPrice() + float(1.5);
    }
};

class addSausage : public Decorator {
public:
    explicit addSausage(HandPancake *handPancake): Decorator(handPancake) {
        std::cout << "addSausage Hello" << std::endl;
    };
    ~addSausage() override {
        std::cout << "addSausage Bye" << std::endl;
    }
    std::string offerHandPancake() override {
        return Decorator::offerHandPancake() + ",加了火腿肠";
    }
    float calcPrice() override {
        return Decorator::calcPrice() + 1;
    }
};

class addVegetable : public Decorator {
public:
    explicit addVegetable(HandPancake *handPancake): Decorator(handPancake) {
        std::cout << "addVegetable Hello" << std::endl;
    };
    ~addVegetable() override {
        std::cout << "addVegetable Bye" << std::endl;
    }
    std::string offerHandPancake() override {
        return Decorator::offerHandPancake() + ",加了青菜";
    }
    float calcPrice() override {
        return Decorator::calcPrice() + float(0.5);
    }
};
```

## Customer

```cpp
/// Customer 顾客
class Customer {
public:
    explicit Customer(const std::string& name) {
        this->name = name;
        std::cout << "Customer " << name <<" Hello" << std::endl;
    }
    ~Customer() {
        delete handPancake;
        std::cout << "Customer " << name <<" Bye" << std::endl;
    }
    void buy(HandPancake *pancake) {
        this->handPancake = pancake;
        // std::setiosflags(std::ios::fixed) << std::setprecision(2)  控制浮点型小数点后输出的位数并自动补0
        std::cout << name + "购买了:" << pancake->offerHandPancake()
                  << ",共花了:" << std::setiosflags(std::ios::fixed) << std::setprecision(2) << pancake->calcPrice() << "元钱" << std::endl;
    }

private:
    std::string name;
    HandPancake *handPancake = nullptr;
};
```





## 测试

```cpp
int main() {

    //有个 张三 的顾客,他要了一个基础3元的手抓饼
    auto *customerA = new Customer("张三");
    customerA->buy(new ConcreteHandPancake(Base3));
    delete customerA;
    std::cout << "================" << std::endl;
    //有个 李四 的顾客,他要了一个基础5元的手抓饼,加鸡蛋
    auto *customerB = new Customer("李四");
    customerB->buy(new addEgg(new ConcreteHandPancake(Base5)));
    delete customerB;
    std::cout << "================" << std::endl;
    //有个 王五 的顾客,他要了一个基础5元的手抓饼,加鸡蛋,加火腿，加青菜。不愧是 钻石王老五
    auto *customerC = new Customer("王五");
    customerC->buy(new addVegetable(new addSausage(new addEgg(new ConcreteHandPancake(Base5)))));
    delete customerC;

    return 0;
}
```

## 输出

![image-20201231134723260](\upload\设计模式之装饰器模式\A_设计模式之装饰器模式.png)





*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

