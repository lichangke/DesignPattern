更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍

## 意图：

**适配器模式(Adapter Pattern)：** 将一个接口转换成客户希望的另一个接口，使接口不兼容的那些类可以一起工作。适配器模式既可以作为类结构型模式，也可以作为对象结构型模式。

## 解决问题：

主要解决在软件系统中，常常要将一些"现存的对象"放到新的环境中，而新环境要求的接口是现对象不能满足的。

## 实现概述：

适配器模式有两种实现方式：**类适配器和对象适配器**。其中，**类适配器使用继承关系来实现，对象适配器使用组合关系来实现**。

两种实现如何选择。以下可做参考：

判断的标准主要有两个，**一个是 Adaptee 接口的个数，另一个是 Adaptee 和 ITarget 的契合程度。**

如果 Adaptee 接口并不多，那两种实现方式都可以。

如果 Adaptee 接口很多，而且 Adaptee 和 ITarget 接口定义大部分都相同，那推荐使用类适配器，因为 Adaptor 复用父类 Adaptee 的接口，比起对象适配器的实现方式，Adaptor 的代码量要少一些。

如果 Adaptee 接口很多，而且 Adaptee 和 ITarget 接口定义大部分都不相同，那推荐使用对象适配器，因为组合结构相对于继承更加灵活。



## 要点：

适配器继承或依赖已有的对象，实现想要的目标接口。

## 应用场景：

- 封装有缺陷的接口设计

  外部系统在接口设计方面有缺陷，引入之后会影响到自身代码，为了隔离设计上的缺陷可以使用适配器模式抽象出更好的接口设计

- 统一多个类的接口设计

  某个功能的实现依赖多个外部系统（或者说类）。通过适配器模式，将它们的接口适配为统一的接口定义，然后我们就可以使用多态的特性来复用代码逻辑。比如统一多款第三方敏感词过滤系统的接口。

- 替换依赖的外部系统

  当我们把项目中依赖的一个外部系统替换为另一个外部系统的时候，利用适配器模式，可以减少对代码的改动。

- 兼容老版本接口

  在做版本升级的时候，对于一些要废弃的接口，不直接将其删除，而是暂时保留，并且标注为 deprecated，并在内部委托为新的接口实现。

- 适配不同格式的数据

  还可以用在不同格式的数据之间的适配。比如，把收集的不同存储格式的数据，统一为相同的格式，以方便存储和使用。

### 生活中场景

读卡器、电源适配器等各种转接头

### 软件中场景

JAVA 中的 jdbc

## 优点：

(1)  **将目标类和适配者类解耦**，通过引入一个适配器类来重用现有的适配者类，无须修改原有结构。
(2)  增加了类的**透明性**和**复用性**，对于客户端类而言是透明的，同一个适配者类可以在多个不同的系统中复用。
(3)  **灵活性**和**扩展性**都非常好，通过使用配置文件，可以很方便地更换适配器，也可以在不修改原有代码的基础上增加新的适配器类，完全符合“开闭原则”。

## 缺点：

- 对编程语言的限制，由于某些语言不支持多继承，一次最多只能适配一个适配者类，比如Java不支持多重继承，不能同时适配多个适配者类；
- 过多地使用适配器，会让系统非常零乱，可读性变差不易整体进行把握，比如，明明看到调用的是 A 接口，其实内部被适配成了 B 接口的实现

# 模式结构

- **Target（目标抽象类）：** 目标抽象类定义客户所需接口，可以是一个抽象类或接口，也可以是具体类。
- **Adapter（适配器类）：**  **适配器类是适配器模式的核心**，可以调用另一个接口，作为一个转换器，对Adaptee和Target进行适配。
- **Adaptee（适配者类）：** 适配者即被适配的角色，它定义了一个已经存在的接口，这个接口需要适配，适配者类一般是一个具体类，包含了客户希望使用的业务方法，在某些情况下可能没有适配者类的源代码只有接口。

类适配器:

![设计模式之适配器模式_类适配器](\upload\设计模式之适配器模式\设计模式之适配器模式_类适配器.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229222232701.jpg)



对象适配器:

![设计模式之适配器模式_对象适配器](\upload\设计模式之适配器模式\设计模式之适配器模式_对象适配器.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229222243923.jpg)



# 代码示例

敏感词过滤

## GitHub

类适配器:

[ClassAdapter](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E9%80%82%E9%85%8D%E5%99%A8%E6%A8%A1%E5%BC%8F/ClassAdapter)

对象适配器:

[Objectadapter](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E9%80%82%E9%85%8D%E5%99%A8%E6%A8%A1%E5%BC%8F/Objectadapter)



## Target（目标抽象类）

```cpp
/// Target（目标抽象类）
class FilterTarget {
public:
    virtual ~FilterTarget() = default;
    virtual void filter(std::string text) = 0;

protected:
    FilterTarget() = default;
};
```

## Adaptee（适配者类）

```cpp
/// Adaptee（适配者类）
class FilterAdaptee_A {
public:
    FilterAdaptee_A() {
        std::cout << "FilterAdaptee_A Hello" << std::endl;
        type = "FilterAdaptee_A";
    }
    ~FilterAdaptee_A() {
        std::cout << "FilterAdaptee_A Bye" << std::endl;
    }
    void adapteeFilter(const char *text) {
        std::cout <<"过滤器为：" << type << std::endl;
        std::cout <<"过滤内容为：" << text << std::endl;
    }

private:
    std::string type;
};

class FilterAdaptee_B {
public:
    FilterAdaptee_B() {
        std::cout << "FilterAdaptee_B Hello" << std::endl;
        type = "FilterAdaptee_B";
    }
    ~FilterAdaptee_B() {
        std::cout << "FilterAdaptee_B Bye" << std::endl;
    }
    void adapteeFilter(const std::string& text, const std::string& mask) {
        std::cout <<"过滤器为：" << type << std::endl;
        std::cout <<"过滤内容为：" << text << std::endl;
        std::cout <<"过滤mask为：" << mask << std::endl;

    }

private:
    std::string type;
};
```



## Adapter（适配器类）

类适配器：

```cpp

/// Adapter（适配器类）
class FilterAdapter_A: public FilterTarget, private FilterAdaptee_A {
public:
    FilterAdapter_A() {
        std::cout << "Class FilterAdapter_A Hello" << std::endl;
    }
    ~FilterAdapter_A() override {
        std::cout << "Class FilterAdapter_A Bye" << std::endl;
    }

    void filter(const std::string text) override {
        const char *temp = text.c_str();
        adapteeFilter(temp);
    }
};

class FilterAdapter_B: public FilterTarget, private FilterAdaptee_B {
public:
    FilterAdapter_B() {
        std::cout << "Class FilterAdapter_B Hello" << std::endl;
        mask = "MASK_B";
    }
    ~FilterAdapter_B() override {
        std::cout << "Class FilterAdapter_B Bye" << std::endl;
    }

    void filter(const std::string text) override {
        adapteeFilter(text,mask);
    }

private:
    std::string mask;
};
```



对象适配器:

```cpp
/// Adapter（适配器类）
class FilterAdapter_A: public FilterTarget {
public:
    FilterAdapter_A() {
        std::cout << "Object FilterAdapter_A Hello" << std::endl;
    }
    ~FilterAdapter_A() override {
        std::cout << "Object FilterAdapter_A Bye" << std::endl;
    }

    void filter(const std::string text) override {
        const char *temp = text.c_str();
        filterAdapteeA.adapteeFilter(temp); // 委托
    }

private:
    FilterAdaptee_A filterAdapteeA;
};

class FilterAdapter_B: public FilterTarget {
public:
    FilterAdapter_B() {
        std::cout << "Object FilterAdapter_B Hello" << std::endl;
        mask = "MASK_B";
    }
    ~FilterAdapter_B() override {
        std::cout << "Object FilterAdapter_B Bye" << std::endl;
    }

    void filter(const std::string text) override {
        filterAdapteeB.adapteeFilter(text,mask);
    }

private:
    FilterAdaptee_B filterAdapteeB;
    std::string mask;
};
```





## 测试

```cpp
int main() {
    std::list<FilterTarget *> filterList;
    filterList.push_back(new FilterAdapter_A());
    filterList.push_back(new FilterAdapter_B());

    std::list<FilterTarget *>::iterator iter; //声明一个迭代器
    iter = filterList.begin();
    while (iter!=filterList.end()) {
        FilterTarget * filter = *iter++;
        filter->filter("this is a Adapter Design Pattern Demo");
    }

    while(!filterList.empty()) {
        FilterTarget * filter = filterList.front();
        filterList.pop_front();
        delete filter;
    }

    return 0;
}
```



## 输出

类适配器：

![image-20201229174107800](\upload\设计模式之适配器模式\A_设计模式之适配器模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229222311574.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

对象适配器：

![image-20201229174900139](\upload\设计模式之适配器模式\B_设计模式之适配器模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229222322943.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

