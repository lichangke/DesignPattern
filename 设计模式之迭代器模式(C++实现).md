更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)



# 介绍

在软件开发中，经常需要使用聚合对象来存储一系列数据。聚合对象拥有两个职责：**一是存储数据；二是遍历数据。** 其中储数据是聚合对象的基本职责；可以将遍历数据的行为从聚合对象中分离出来，封装在一个被称之为“**迭代器**”的对象中，由迭代器来提供遍历聚合对象内部数据的行为，这将简化聚合对象的设计。

## 意图：

**迭代器模式(Iterator Pattern)：**提供一种方法来访问聚合对象，而不用暴露这个对象的内部表示，其别名为游标(Cursor)。迭代器模式是一种对象行为型模式。

## 解决问题：

分离聚合对象的数据存储与数据遍历，将数据遍历功能封装在一个被称之为“**迭代器**”的对象中

## 实现概述：

模式结构包含聚合和迭代器两个层次的结构。为方便扩展，迭代器模式常常和工厂方法模式结合。迭代器中需要定义 hasNext()、currentItem()、next() 三个最基本的方法。待遍历的容器对象通过依赖注入传递到迭代器类中。容器通过 iterator() 方法来创建迭代器。

## 应用场景：

- 访问一个聚合对象而无需暴露它的内部结构，将聚合对象的访问与内部数据的存储分离。
- 需要为一个聚合对象提供多种遍历方法。
- 为遍历不同的聚合结构提供一个统一的接口，在该接口的实现类中为不同的聚合结构提供不同的遍历方式，而客户端可以一致性地操作该接口。

### 生活中场景

物流系统中的传送带，不管传送的是什么物品，都会被打包成一个个箱子，并且有一个统一的二维码。这样不需要关心箱子里是什么，在分发时只需要一个个检查发送的目的地即可。

电视机，不管是什么电视机，通过遥控器都可以前进、后退选择电视节目

### 软件中场景

如 Java和C++11中的迭代器

## 优点：

1. 访问一个聚合对象的内容而无须暴露它的内部表示。
2. 遍历任务交由迭代器完成，这简化了聚合类。
3. 它支持以不同方式遍历一个聚合，甚至可以自定义迭代器的子类以支持新的遍历。
4. 增加新的聚合类和迭代器类都很方便，无须修改原有代码。
5. 封装性良好，为遍历不同的聚合结构提供一个统一的接口。

## 缺点：

将聚合类中存储对象和管理对象的职责分离，增加新的聚合类时同样需要考虑增加对应的新的迭代器类，类的个数成对增加，不利于系统管理和维护；

设计难度较大，需要充分考虑将来系统的扩展。

# 模式结构

- **Iterator（抽象迭代器）**：声明了访问和遍历聚合对象元素的接口，如first()方法用于访问聚合对象中第一个元素，next()方法用于访问下一个元素，hasNext()判断是否还有下一个元素，currentItem()方法用于获取当前元素。
- **ConcreteIterator（具体迭代器）**：实现抽象迭代器声明的方法，完成对聚合对象的遍历，通常具体迭代器中会专门用一个变量（称为**游标**）来记录迭代器在聚合对象中所处的位置。游标通常是一个表示位置的非负整数。
- **Aggregate（抽象聚合类）**：用于存储和管理元素对象，声明一个createIterator()方法用于创建一个迭代器对象，充当抽象迭代器工厂角色。
- **ConcreteAggregate（具体聚合类）**：实现了方法createIterator()，该方法返回一个与该具体聚合类对应的具体迭代器ConcreteIterator的实例。

![设计模式之迭代器模式](\upload\设计模式之迭代器模式\设计模式之迭代器模式.jpg)



# 代码示例



电视机，不管是什么电视机，通过遥控器都可以前进、后退选择电视节目，并且通过输入具体数值 i (i>=0)选台。这里电视台号从0开始，使用数组存储（可以自己实现动态扩容数组）。0 后退为 Max，MAX 前进为0，若 i > Max ,则选择为Max。

Iterator（抽象迭代器）：Iterator

ConcreteIterator（具体迭代器）：TVRemote

Aggregate（抽象聚合类）：Aggregate

ConcreteAggregate（具体聚合类）：Television



## GitHub



[IteratorPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E8%BF%AD%E4%BB%A3%E5%99%A8%E6%A8%A1%E5%BC%8F/IteratorPattern)



## Iterator（抽象迭代器）

```cpp
/// Iterator（抽象迭代器）：Iterator
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void nextChannel() = 0; // 下一个电视台节目
    virtual void preChannel() = 0; // 上一个电视台节目
    virtual void chooseChannel(int i) = 0; // 选择具体哪个台
    virtual int getChannel() = 0; // 获取当前频道
protected:
    Iterator() = default;
};
```



## Aggregate（抽象聚合类）

```cpp
/// Aggregate（抽象聚合类）：Aggregate
class Aggregate {
public:
    virtual ~Aggregate()= default;
    virtual Iterator* createIterator() = 0;
    virtual void play(int i) = 0;
protected:
    Aggregate()= default;
};
```

## ConcreteAggregate（具体聚合类）

```cpp
/// ConcreteAggregate（具体聚合类）：Television
class Television : Aggregate{

public:
    explicit Television(const std::vector<std::string> &vector) {
        std::cout << "Television Hello" << std::endl;
        channelVector = vector;
    }
    ~Television() override {
        std::cout << "Television Bye" << std::endl;
    }

    // 实现创建迭代器
    Iterator* createIterator() override;

    void play(int i) override{
        std::cout << "现在播放： " <<  channelVector[i] << std::endl;
    }

    int getTotalChannelCount() { // 获取频道总数
        return channelVector.size();
    }
    void addChannel(const std::string& channel) { // 补充添加频道
        std::cout << "补充添加节目频道： " <<  channel << std::endl;
        channelVector.emplace_back(channel);
    }

private:
    std::vector<std::string> channelVector; //
};
// 由于 在一个文件中 所以 此函数 放在 TVRemote 类后
Iterator *Television::createIterator() {
    // 实现创建迭代器
    auto *iter = new TVRemote();
    iter->bindTV(this);
    return iter;
}
```

## ConcreteIterator（具体迭代器）

```cpp
/// ConcreteIterator（具体迭代器）：TVRemote
class TVRemote : public  Iterator {
public:
    TVRemote() {
        tv = nullptr;
        cursor = -1;
        totalCount = -1;
        boundTV = false;
        std::cout << "TVRemote Hello" << std::endl;
    }
    ~TVRemote() override {
        std::cout << "TVRemote Bye" << std::endl;
    }

    void bindTV(Television *television) { // 绑定 遥控器和TV
        this->tv = television;
        cursor = 0;
        boundTV = true;
        totalCount = tv->getTotalChannelCount();
    }

    // 下一个电视台节目
    void nextChannel() override {
        assert(boundTV);
        totalCount = tv->getTotalChannelCount();
        cursor++;
        if(cursor > totalCount - 1) {
            cursor = 0;
        }
        std::cout << "TVRemote next channel, current = " << cursor << std::endl;
        tv->play(cursor);
    }

    // 上一个电视台节目
    void preChannel() override {
        assert(boundTV);
        totalCount = tv->getTotalChannelCount();
        cursor--;
        if(cursor < 0) {
            cursor = totalCount - 1;
        }
        std::cout << "TVRemote pre channel, current = " << cursor << std::endl;
        tv->play(cursor);
    }
    // 选择具体哪个台
    void chooseChannel(int i) override {
        assert(boundTV);
        totalCount = tv->getTotalChannelCount();
        if (i > totalCount - 1) {
            cursor = totalCount - 1;
        } else if (i < 0) {
            cursor = 0;
        } else {
            cursor = i;
        }
        std::cout << "TVRemote choose channel = " << cursor << std::endl;
        tv->play(cursor);
    }

    int getChannel() override {
        return cursor;
    }
private:
    bool boundTV; // 是否绑定TV
    Television *tv; // 绑定的电视TV
    int cursor; // 游标
    int totalCount; // 最大 频道数目
};
```





## 测试

```cpp
int main() {

    std::vector<std::string> channelvector = { "综合频道", "财经频道", "综艺频道", "体育频道", "电影频道", "电视剧频道", "纪录频道", "科教频道" , "新闻频道"};
    std::string addChannel1 = "社会与法频道", addChannel2 = "少儿频道";
    // 创建电视
    auto *tv = new Television(channelvector);
    // 创建遥控器
    Iterator *tvRemote = tv->createIterator();

    // 注 频道0为 综合频道； 频道1为 财经频道 ；以此类推
    // 选择频道 5
    std::cout << "选择频道 5" << std::endl;
    tvRemote->chooseChannel(5);
    // 遍历电视所有频道
    std::cout << "以选择频道 5 为基础 顺序 遍历所有频道 " << std::endl;
    do {
        tvRemote->nextChannel();
    } while(5!=tvRemote->getChannel());

    std::cout << "添加 2 个补充频道" << std::endl;
    tv->addChannel(addChannel1);
    tv->addChannel(addChannel2);

    // 选择频道 6
    std::cout << "选择频道 6" << std::endl;
    tvRemote->chooseChannel(6);
    // 遍历电视所有频道
    std::cout << "以选择频道 6 为基础 逆序 遍历所有频道 " << std::endl;
    do {
        tvRemote->nextChannel();
    } while(6!=tvRemote->getChannel());

    delete tv;
    delete tvRemote;
    return 0;
}
```



## 输出

![A_设计模式之迭代器模式](\upload\设计模式之迭代器模式\A_设计模式之迭代器模式.png)

![image-20210106223352802](\upload\设计模式之迭代器模式\B_设计模式之迭代器模式.png)





*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

