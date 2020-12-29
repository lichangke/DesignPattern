# 介绍

建造者模式是较为复杂的创建型模式，它将客户端与包含多个组成部分（或部件）的复杂对象的创建过程分离，客户端无须知道复杂对象的内部组成部分与装配方式，只需要知道所需建造者的类型即可。

## 意图：

**建造者模式(Builder Pattern)：**将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。建造者模式是一种对象创建型模式。

## 解决问题：

主要解决在软件系统中，有时候面临着"一个复杂对象"的创建工作，其通常由各个部分的子对象用一定的算法构成；由于需求的变化，这个复杂对象的各个部分经常面临着剧烈的变化，但是将它们组合在一起的算法却相对稳定。



## 要点：

将变与不变分离开。建造者：创建和提供实例，导演：管理建造出来的实例的依赖关系。



## 应用场景：

(1) 需要生成的产品对象有复杂的内部结构，这些产品对象通常包含多个成员属性。

(2) 需要生成的产品对象的属性相互依赖，需要指定其生成顺序。

(3) 对象的创建过程独立于创建该对象的类。在建造者模式中通过引入了指挥者类，将创建过程封装在指挥者类中，而不在建造者类和客户类中。

(4) 隔离复杂对象的创建和使用，并使得相同的创建过程可以创建不同的产品。

### 生活中场景

去肯德基，汉堡、可乐、薯条、炸鸡翅等是不变的，而其组合是经常变化的，生成出所谓的"套餐"。 

### 软件中场景

JAVA 中的 StringBuilder。

## 优点：

(1) 在建造者模式中，客户端不必知道产品内部组成的细节，将产品本身与产品的创建过程解耦，使得相同的创建过程可以创建不同的产品对象。

(2) 每一个具体建造者都相对独立，而与其他的具体建造者无关，因此可以很方便地替换具体建造者或增加新的具体建造者，用户使用不同的具体建造者即可得到不同的产品对象。

(3) 可以更加精细地控制产品的创建过程。将复杂产品的创建步骤分解在不同的方法中，使得创建过程更加清晰，也更方便使用程序来控制创建过程。

## 缺点：

(1) 建造者模式所创建的产品一般**具有较多的共同点**，其组成部分相似，如果产品之间的差异性很大，例如很多组成部分都不相同，不适合使用建造者模式，因此其使用范围受到一定的限制。

(2) 如果产品的内部变化复杂，可能会导致需要定义很多具体建造者类来实现这种变化，导致系统变得很庞大，增加系统的理解难度和运行成本。



# 模式结构

- **抽象建造者（AbstractBuilder）**：创建一个Product对象的各个部件指定的抽象接口；一般声明两类方法，一类方法是buildPartX()，它们用于创建复杂对象的各个部件；另一类方法是getResult()，它们用于返回复杂对象。
- **具体建造者（ConcreteBuilder）**：实现AbstractBuilder的接口，实现各个部件的具体构造和装配方法，定义并明确它所创建的复杂对象，也可以提供一个方法返回创建好的复杂产品对象。
- **产品角色（Product）**：被构建的复杂对象，包含多个组成部件，具体建造者创建该产品的内部表示并定义它的装配过程。
- **指挥者（Director）**： 指挥者又称为导演类，它负责安排复杂对象的建造次序，指挥者与抽象建造者之间存在关联关系，可以在其construct()建造方法中调用建造者对象的部件构造与装配方法，完成复杂对象的建造。**客户端一般只需要与Director交互，指定建造者类型，然后通过构造函数或者setter方法将具体建造者对象传入Director**。它主要作用是：隔离客户与对象的生产过程，并负责控制产品对象的生产过程。



![设计模式之建造者模式](\upload\设计模式之建造者模式\设计模式之建造者模式.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201228215417256.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)





# 代码示例

使用建造者模式生成不同快餐套餐。一个典型的套餐可以是一个汉堡（Burger）、一杯饮料（ Drink）和一份小吃（Snacks）。汉堡（Burger）可以是素食汉堡（Veg Burger）或鸡肉汉堡（Chicken Burger），饮料（Drink）可以是可口可乐（coke）或百事可乐（pepsi）或者咖啡（cafe），小吃（Snacks）可以是炸薯条（French fries）或 洋葱圈（Onion rings）



## GitHub

[BuilderPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E5%BB%BA%E9%80%A0%E8%80%85%E6%A8%A1%E5%BC%8F/BuilderPattern)

## 产品角色（Product）

```cpp
/// 产品角色（Product）
class ProductMeal {
public:
    ProductMeal() {
        std::cout << "ProductMeal Hello" << std::endl;
    };
    ~ProductMeal() {
        std::cout << "ProductMeal Bye" << std::endl;
    };
    void setBurger(const std::string &iburger) {
        mBurger = iburger;
    }
    void setDrink(const std::string &idrink) {
        mDrink = idrink;
    }
    void setSnacks(const std::string &isnacks) {
        mSnacks = isnacks;
    }

    void showMeal(){
        std::cout << "Burger is " << mBurger << std::endl;
        std::cout << "Drink is " << mDrink << std::endl;
        std::cout << "Snacks is " << mSnacks << std::endl;
    }

private:
    std::string mBurger;
    std::string mDrink;
    std::string mSnacks;
};
```
## 抽象建造者（AbstractBuilder）
```cpp
/// 抽象建造者（AbstractBuilder）
class AbstractBuilder
{
public:
    virtual ~AbstractBuilder() = default;
    //抽象方法：
    virtual void buildBurger() = 0;
    virtual void buildDrink() = 0;
    virtual void buildSnacks() = 0;
    virtual ProductMeal* getMeal() = 0;

protected:
    AbstractBuilder()= default;

};
```

## 具体建造者（ConcreteBuilder）

```cpp
/// 具体建造者（ConcreteBuilder）
class ConcreteBuilderMeal_A : public AbstractBuilder{ /// 套餐A
public:
    ConcreteBuilderMeal_A(){
        std::cout << "ConcreteBuilderMeal_A Hello" << std::endl;
        meal = new ProductMeal();
    }
    ~ConcreteBuilderMeal_A() override{
        std::cout << "ConcreteBuilderMeal_A Bye" << std::endl;
        delete meal;
    }
    void buildBurger() override {
        meal->setBurger("Veg Burger");
    };
    void buildDrink() override {
        meal->setDrink("coke");
    }
    void buildSnacks() override {
        meal->setSnacks("French fries");
    }
    ProductMeal* getMeal() override {
        return meal;
    }
private:
    ProductMeal *meal;
};

class ConcreteBuilderMeal_B : public AbstractBuilder{ /// 套餐B
public:
    ConcreteBuilderMeal_B(){
        std::cout << "ConcreteBuilderMeal_B Hello" << std::endl;
        meal = new ProductMeal();
    }
    ~ConcreteBuilderMeal_B() override{
        std::cout << "ConcreteBuilderMeal_B Bye" << std::endl;
        delete meal;
    }
    void buildBurger() override {
        meal->setBurger("Chicken Burger");
    };
    void buildDrink() override {
        meal->setDrink("pepsi");
    }
    void buildSnacks() override {
        meal->setSnacks("Onion rings");
    }
    ProductMeal* getMeal() override {
        return meal;
    }
private:
    ProductMeal *meal;
};
class ConcreteBuilderMeal_C : public AbstractBuilder{ /// 套餐C
public:
    ConcreteBuilderMeal_C(){
        std::cout << "ConcreteBuilderMeal_C Hello" << std::endl;
        meal = new ProductMeal();
    }
    ~ConcreteBuilderMeal_C() override{
        std::cout << "ConcreteBuilderMeal_C Bye" << std::endl;
        delete meal;
    }
    void buildBurger() override {
        meal->setBurger("Veg Burger");
    };
    void buildDrink() override {
        meal->setDrink("cafe");
    }
    void buildSnacks() override {
        meal->setSnacks("French fries");
    }
    ProductMeal* getMeal() override {
        return meal;
    }
private:
    ProductMeal *meal;
};
```



## 指挥者（Director）

```cpp
/// 指挥者（Director）
class Director
{
public:
    Director() {
        std::cout << "Director Hello" << std::endl;
    };
    ~Director() {
        std::cout << "Director Bye" << std::endl;
    }
    //具体实现方法
    void setBuilder(AbstractBuilder *iBuilder){
        this->builder = iBuilder;
    }
    //封装组装流程，返回建造结果
    ProductMeal *construct(){
        assert(builder!= nullptr);
        builder->buildBurger(); /// 制作顺序
        builder->buildDrink();
        builder->buildSnacks();
        return builder->getMeal();
    }
private:
    AbstractBuilder *builder= nullptr;
};
```



## 测试

```cpp
int main() {

    //指挥者
    Director director;
    //抽象建造者
    AbstractBuilder *builder;
    //产品：套餐
    ProductMeal *meal;

    //指定具体建造者A
    builder = new ConcreteBuilderMeal_A();
    director.setBuilder(builder);
    meal = director.construct();
    meal->showMeal();
    delete builder;
    std::cout << "======================" << std::endl;
    //指定具体建造者C
    builder = new ConcreteBuilderMeal_C();
    director.setBuilder(builder);
    meal = director.construct();
    meal->showMeal();
    delete builder;
    std::cout << "======================" << std::endl;
    //指定具体建造者B
    builder = new ConcreteBuilderMeal_B();
    director.setBuilder(builder);
    meal = director.construct();
    meal->showMeal();
    delete builder;

    getchar();
    return 0;
}
```



## 输出

![image-20201228164654077](\upload\设计模式之建造者模式\A_设计模式之建造者模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201228215445353.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



# 建造者模式VS工厂模式



**工厂模式**是用来创建**不同但是相关类型**的对象（继承同一父类或者接口的一组子类），由给定的参数来决定创建哪种类型的对象。**建造者模式**是用来创建**一种类型的复杂对象**，通过设置不同的可选参数，“定制化”地创建不同的对象。





*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

