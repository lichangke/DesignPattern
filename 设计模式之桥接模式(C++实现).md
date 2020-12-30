# 介绍

桥接（Bridge）是用于把抽象化与实现化解耦，使得二者可以独立变化。这种类型的设计模式属于结构型模式，它通过提供抽象化和实现化之间的桥接结构，来实现二者的解耦。

## 意图：

对于桥接模式“最纯正”的理解方式，当属 GoF 的《设计模式》一书中对桥接模式的定义。

> Decouple an abstraction from its implementation so that the two can vary independently。
>
> 翻译成中文就是：“将抽象和实现解耦，让它们可以独立变化。

定义中的“**抽象**”，指的并**非“抽象类”或“接口”**，而是被抽象出来的一套**“类库”**，它只包含骨架代码，真正的业务逻辑需要委派给定义中的**“实现”**来完成。而定义中的“实现”，也并**非“接口的实现类”**，而是一套独立的“**类库”**。“抽象”和“实现”独立开发，通过对象之间的**组合关系**，组装在一起。



关于桥接模式，很多书籍、资料中，还有另外一种理解方式：

> 一个类存在两个（或多个）独立变化的维度，我们通过组合的方式，让这两个（或多个）维度可以独立进行扩展。
>
> 通过组合关系来替代继承关系，避免继承层次的指数级爆炸。



## 解决问题：

在软件开发中如果一个类或一个系统有多个变化维度时，都可以尝试使用桥接模式对其进行设计，桥接模式为多维度变化的系统提供了一套完整的解决方案，并且降低了系统的复杂度。



## 实现概述：

把多角度变化分离出来，让它们独立变化，减少它们之间耦合。

## 要点：

将两个或多个独立变化的维度设计为两个或多个独立的继承等级结构，并且在抽象层建立一个或多个抽象关联，这些关联关系类似一条条连接两个独立继承结构的桥，故名桥接模式。

用**抽象关联**取代了传统的**多层继承**，将类之间的静态继承关系转换为动态的对象组合关系。



## 应用场景：

​    (1)如果一个系统需要在抽象化和具体化之间增加更多的灵活性，避免在两个层次之间建立静态的继承关系，通过桥接模式可以使它们在抽象层建立一个关联关系。

​    (2)“抽象部分”和“实现部分”可以以继承的方式独立扩展而互不影响，在程序运行时可以动态将一个抽象化子类的对象和一个实现化子类的对象进行组合，即系统需要对抽象化角色和实现化角色进行动态耦合。

​    (3)一个类存在两个（或多个）独立变化的维度，且这两个（或多个）维度都需要独立进行扩展。

​    (4)对于那些不希望使用继承或因为多层继承导致系统类的个数急剧增加的系统，桥接模式尤为适用。



## 优点：

- 分离抽象接口与实现部分，使用对象间的关联关系使抽象与实现解耦；
- 在很多情况下，桥接模式可以取代多层继承方案，多层继承方案违背了“单一职责原则”，复用性较差，且类的个数非常多，能使多继承的M*N个类解决方式，变为M+N个类解决。
- 桥接模式提高了系统可扩展性，某个维度需要扩展只需增加实现类接口或者具体实现类，而且不影响另一个维度，符合开闭原则。

## 缺点：

- 桥接模式的使用会增加系统的理解与设计难度，因为关联关系建立在抽象层，需要一开始就在抽象层进行设计与编程；
- 桥接模式要求正确识别出系统中两个或多个独立变化的维度，如何准确识别系统中的两个维度是应用桥接模式的难点。

# 模式结构

- **Abstraction（抽象类） ：** 用于定义抽象类的接口，它一般是抽象类，定义了一个Implementor（实现类接口）类型的对象，与其之间具有关联关系，从而分离抽象接口与实现部分

- **RefinedAbstraction（扩充抽象类）：** 扩充由Abstraction定义的接口，通常情况下它是具体类，实现Abstraction的抽象业务方法，并可以调用在Implementor中定义的业务方法。

- **Implementor（实现类接口）： ** 定义实现类的接口，Implementor接口声明了一些基本操作，而具体实现交给其子类。通过关联关系，在Abstraction中不仅拥有自己的方法，还可以调用到Implementor中定义的方法，使用关联关系来替代继承关系。

- **ConcreteImplementor（具体实现类）：** 具体实现Implementor接口，在不同的ConcreteImplementor中提供基本操作的不同实现。



![设计模式之桥接模式](\upload\设计模式之桥接模式\设计模式之桥接模式.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020123021282421.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



# 代码示例

绘制不同形状(Circle 、Rectangle )不同颜色(Red、Green、Blue)的图形(Shape)

Abstraction（抽象类） ：ShSape

RefinedAbstraction（扩充抽象类）：Circle 、Rectangle

Implementor（实现类接口）： Color

ConcreteImplementor（具体实现类）：Red、Green、Blue

## GitHub

[BridgePattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E6%A1%A5%E6%8E%A5%E6%A8%A1%E5%BC%8F/BridgePattern)



## Implementor（实现类接口）： 

```cpp
/// Implementor（实现类接口）： Color
class Color {
public:
    virtual ~Color() = default;
    virtual void fillColor() = 0;
};
```

## ConcreteImplementor（具体实现类）：

```cpp
/// ConcreteImplementor（具体实现类）：Red、Green、Blue
class Red : public Color {
public:
    Red() {
        std::cout << "Red Hello" << std::endl;
        colorType = "Red";
    }
    ~Red() override {
        std::cout << "Red Bye" << std::endl;
    }
    void fillColor() override {
        std::cout << "填充颜色： " << colorType << std::endl;
    }

private:
    std::string colorType;
};

class Green : public Color {
public:
    Green() {
        std::cout << "Green Hello" << std::endl;
        colorType = "Green";
    }
    ~Green() override {
        std::cout << "Green Bye" << std::endl;
    }
    void fillColor() override {
        std::cout << "填充颜色： " << colorType << std::endl;
    }

private:
    std::string colorType;
};

class Blue : public Color {
public:
    Blue() {
        std::cout << "Blue Hello" << std::endl;
        colorType = "Blue";
    }
    ~Blue() override {
        std::cout << "Blue Bye" << std::endl;
    }
    void fillColor() override {
        std::cout << "填充颜色： " << colorType << std::endl;
    }

private:
    std::string colorType;
};
```

## Abstraction（抽象类） :

```cpp
/// Abstraction（抽象类） : Shape
class Shape {
public:
    virtual ~Shape() = default;
    virtual void showShape() = 0;
    virtual void chooseColor(Color *col) = 0;
protected:
    virtual void drawShape() = 0;
    virtual void drawColor() = 0;
    Color *color = nullptr;

```

## RefinedAbstraction（扩充抽象类）：

```cpp
/// RefinedAbstraction（扩充抽象类）：Circle 、Rectangle
class Circle : public Shape {
public:
    Circle() {
        std::cout << "Circle Hello" << std::endl;
        shapeType = "Circle";
    }
    ~Circle() override {
        std::cout << "Circle Bye" << std::endl;
        delete color;
    }
    void showShape() override {
        drawShape();
        drawColor();
    }
    void chooseColor(Color *col) override {
        color = col;
    }
private:
    void drawShape() override {
        std::cout << "绘制图形： " << shapeType << std::endl;
    }
    void drawColor() override {
        color->fillColor();
    }
    std::string shapeType;
};

class Rectangle : public Shape {
public:
    Rectangle() {
        std::cout << "Rectangle Hello" << std::endl;
        shapeType = "Rectangle";
    }
    ~Rectangle() override {
        std::cout << "Rectangle Bye" << std::endl;
        delete color;
    }
    void showShape() override {
        drawShape();
        drawColor();
    }
    void chooseColor(Color *col) override {
        color = col;
    }
private:
    void drawShape() override {
        std::cout << "绘制图形： " << shapeType << std::endl;
    }
    void drawColor() override {
        color->fillColor();
    }
    std::string shapeType;
};
```





## 测试

```cpp
int main() {

    Shape *shape;
    //绘制 红色 圆形
    std::cout << "=====绘制 红色 圆形=====" << std::endl;
    shape = new Circle();
    shape->chooseColor(new Red());
    shape->showShape();
    delete shape;

    //绘制 绿色 圆形
    std::cout << "=====绘制 绿色 圆形=====" << std::endl;
    shape = new Circle();
    shape->chooseColor(new Green());
    shape->showShape();
    delete shape;

    //绘制 蓝色 矩形
    std::cout << "=====绘制 蓝色 矩形=====" << std::endl;
    shape = new Rectangle();
    shape->chooseColor(new Blue());
    shape->showShape();
    delete shape;

    return 0;
}
```

## 输出

![image-20201230135621468](\upload\设计模式之桥接模式\A_设计模式之桥接模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201230212843558.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)





*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

