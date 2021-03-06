更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍

所谓“享元”，顾名思义就是被共享的单元。享元模式的意图是复用对象，节省内存，前提是享元对象是**不可变对象**。

“不可变对象”指的是，一旦通过构造函数初始化完成之后，它的状态（对象的成员变量或者属性）就不会再被修改了。

## 意图：

**享元模式(Flyweight Pattern)：**运用共享技术有效地支持大量细粒度对象的复用。系统只使用少量的对象，而这些对象都很相似，状态变化很小，可以实现对象的多次复用。由于享元模式要求能够共享的对象必须是细粒度对象，因此它又称为轻量级模式，它是一种对象结构型模式。

## 解决问题：

在有大量对象时，有可能会造成内存溢出，把其中共同的部分抽象出来，如果有相同的业务请求，直接返回在内存中已有的对象，避免重新创建。

## 实现概述：

通过工厂模式，在工厂类中，可以通过一个 Map 来缓存已经创建过的享元对象，来达到复用的目的。

## 要点：

用 Map 存储对象，享元模式以共享的方式高效地支持大量细粒度对象的重用，享元对象能做到共享的关键是区分了**内部状态(Intrinsic State)和外部状态(Extrinsic State)**。

**内部状态是存储在享元对象内部并且不会随环境改变而改变的状态，内部状态可以共享**。

**外部状态是随环境改变而改变的、不可以共享的状态**。享元对象的外部状态通常由客户端保存，并在享元对象被创建之后，需要使用的时候再传入到享元对象内部。



## 应用场景：

当一个系统中存在大量重复对象的时候，如果这些重复的对象是不可变对象，就可以利用享元模式将对象设计成享元，在内存中只保留一份实例，供多处代码引用。

不仅仅相同对象可以设计成享元，对于相似对象，也可以将这些对象中相同的部分（字段）提取出来，设计成享元，让这些大量相似对象引用这些享元，不同的地方作为外部状态传入对象中。

在使用享元模式时需要维护一个存储享元对象的享元池，而这需要耗费一定的系统资源，因此，应当在需要多次重复使用享元对象时才值得使用享元模式。

### 生活中场景

棋子，比如围棋子，棋子与棋子之间除了颜色和位置，好像没什么不同了吧！也就是说，每个棋子对象的大部分状态都是一样的（形状、材料、质地等）。

### 软件中场景

JAVA 中的 String，如果有则返回，如果没有则创建一个字符串保存在字符串缓存池里面。

Python [CPython（Python 的 C 实现）]内部会对 -5 到 256 的整型维持一个数组， 起到一个缓存的作用。



## 优点：

- 享元模式通过享元池存储已经创建好的享元对象，**实现相同或相似的细粒度对象的复用，大大减少了系统中的对象数量，节约了内存空间，提升了系统性能**；
- 享元模式通过内部状态和外部状态的区分，外部状态相互独立，客户端可以根据需求任意使用。

## 缺点：

- 享元模式需要增加逻辑来取分出内部状态和外部状态，增加了编程的复杂度；



# 模式结构

- **Flyweight（抽象享元类）**：通常是一个接口或抽象类，在抽象享元类中声明了具体享元类公共的方法，这些方法可以向外部提供享元对象的内部状态数据，也可以通过这些方法设置外部状态；
- **ConcreteFlyweight（具体享元类）**：具体实现抽象享元类声明的方法，其实例称为享元对象；具体享元类中为内部状态提供存储空间。**具体享元类通常可以结合[单例模式](https://blog.csdn.net/leacock1991/article/details/111875728)来设计实现，为每个具体享元类提供唯一的享元对象**。
- **UnsharedConcreteFlyweight（非共享具体享元类）**：并不是所有抽象享元类的子类都需要被共享，可以将这些类设计为非共享具体享元类；当需要一个非共享具体享元类的对象时可以直接通过实例化创建。
- **FlyweightFactory（享元工厂类）**：用于创建并管理享元对象，针对抽象享元类编程，将各种具体享元类对象存储在一个享元池中，享元池一般设计为一个存储键值对的集合（或者其他类型的集合），可结合工厂模式设计。客户需要某个享元对象时，如果享元池中已有该对象实例，则返回该实例，否则创建一个新的实例，给客户返回新的实例，并将新实例保存在享元池中。

![设计模式之享元模式](\upload\设计模式之享元模式\设计模式之享元模式.jpg)



# 代码示例

以围棋棋子为例，棋子除了颜色和坐标其他都一样

Flyweight（抽象享元类）：ChessPiece

ConcreteFlyweight（具体享元类）：BlackChessPiece  WhiteChessPiece

UnsharedConcreteFlyweight（非共享具体享元类）：Coordinates

FlyweightFactory（享元工厂类）：ChessPieceFactory



## GitHub

[FlyweightPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E4%BA%AB%E5%85%83%E6%A8%A1%E5%BC%8F/FlyweightPattern)

## UnsharedConcreteFlyweight（非共享具体享元类）

```cpp
/// UnsharedConcreteFlyweight（非共享具体享元类）：Coordinates
class Coordinates {
public:
    Coordinates(int x,int y) {
        this->x = x;
        this->y = y;
        std::cout << "Coordinates Hello, x = "  << x << " y = " << y << std::endl;
    }
    ~Coordinates() {
        std::cout << "Coordinates Bye, x = "  << x << " y = " << y << std::endl;
    }
    int getX() {
        return x;
    }
    void setX(int x) {
        this->x = x;
    }
    int getY() {
        return y;
    }
    void setY(int y) {
        this->y = y;
    }
private:
    int x;
    int y;

};
```

## Flyweight（抽象享元类）

```cpp
/// Flyweight（抽象享元类）：ChessPiece
class ChessPiece {
public:
    virtual ~ChessPiece() = default;
    virtual std::string getColor() = 0;
    void display(Coordinates *coord) {
        std::cout << "棋子颜色：" << getColor()  <<  "，棋子位置："  << "x = "  << coord->getX() <<  "，y = "  << coord->getY() <<  std::endl;
    };
protected:
    ChessPiece() = default;
    std::string color;
};
```



## ConcreteFlyweight（具体享元类）

```cpp
/// ConcreteFlyweight（具体享元类）：BlackChessPiece  WhiteChessPiece
class BlackChessPiece : public ChessPiece {
public:
    BlackChessPiece() {
        std::cout << "BlackChessPiece Hello" << std::endl;
        color = "黑色";
    }
    ~BlackChessPiece() override {
            std::cout << "BlackChessPiece Bye" << std::endl;
    }
    std::string getColor() override{
        return color;
    }
};

class WhiteChessPiece : public ChessPiece {
public:
    WhiteChessPiece() {
        std::cout << "WhiteChessPiece Hello" << std::endl;
        color = "白色";
    }
    ~WhiteChessPiece() override {
        std::cout << "WhiteChessPiece Bye" << std::endl;
    }
    std::string getColor() override{
        return color;
    }
};
```



## FlyweightFactory（享元工厂类）

```cpp
/// FlyweightFactory（享元工厂类）：ChessPieceFactory
class ChessPieceFactory {
public:
    static ChessPieceFactory *getInstance() {
        static ChessPieceFactory instance;
        return &instance;
    }
    ChessPiece *getChessPiece(const std::string& color) {
        return mapChessPiece[color];
    }
private:
    ChessPieceFactory() {
        std::cout << "ChessPieceFactory Hello" << std::endl;
        mapChessPiece.insert(std::pair<std::string,ChessPiece *>("b",new BlackChessPiece()));
        mapChessPiece.insert(std::pair<std::string,ChessPiece *>("w",new WhiteChessPiece()));
    }
    ~ChessPieceFactory() {
        std::cout << "ChessPieceFactory Bye" << std::endl;
        auto  iter = mapChessPiece.begin();
        while(iter!=mapChessPiece.end()) {
            ChessPiece *chessPiece = iter->second;
            delete chessPiece;
            iter++;
        }
    }

    std::map<std::string,ChessPiece *> mapChessPiece;
};
```



## 测试

```cpp
int main() {
    ChessPiece *black1,*black2,*black3,*white1,*white2;
    ChessPieceFactory *factory;

    //获取享元工厂对象
    factory = ChessPieceFactory::getInstance();

    //通过享元工厂获取三颗黑子
    black1 = factory->getChessPiece("b");
    black2 = factory->getChessPiece("b");
    black3 = factory->getChessPiece("b");
    std::cout << "两颗黑子是否相同：" << (black1==black2) <<  std::endl;

    //通过享元工厂获取两颗白子
    white1 = factory->getChessPiece("w");
    white2 = factory->getChessPiece("w");
    std::cout << "两颗白子是否相同：" << (white1==white2) <<  std::endl;

    std::vector<Coordinates *> coordinates;
    //std::function<Coordinates *(Coordinates *)> func = [&coordinates](Coordinates *coord ) {
    auto func = [&coordinates](Coordinates *coord ) {
        coordinates.push_back(coord);
        return coord;
    };
    //显示棋子
    black1->display(func(new Coordinates(1,3)));
    black2->display(func(new Coordinates(2,6)));;
    black3->display(func(new Coordinates(4,7)));;
    white1->display(func(new Coordinates(5,8)));;
    white2->display(func(new Coordinates(4,1)));;

    for (auto & coordinate : coordinates) {
        delete coordinate;
    }
    return 0;
}
```

## 输出

![image-20210103195852370](\upload\设计模式之享元模式\A_设计模式之享元模式.png)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

