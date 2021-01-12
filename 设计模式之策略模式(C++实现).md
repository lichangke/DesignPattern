更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

[TOC]

# 介绍

软件开发中，实现某一个功能有多条途径，每一条途径对应一种算法，通过策略模式的使用来实现灵活地选择解决途径，方便地增加新的解决途径。工厂模式是解耦对象的创建和使用，观察者模式是解耦观察者和被观察者。策略模式跟两者类似，也能起到解耦的作用，不过，它解耦的是**策略的定义、创建、使用**这三部分。

## 意图：

**策略模式(Strategy Pattern)：** 定义一系列算法类，将每一个算法封装起来，并让它们可以相互替换，策略模式让算法独立于使用它的客户而变化（客户端代指使用算法的代码）。

## 解决问题：

解决某一问题的一个算法族，允许用户从该算法族中任选一个算法来解决某一问题，同时可以方便地更换算法或者增加新的算法。

## 实现概述：

策略类的定义比较简单，包含一个**策略接口**和一组实现这个接口的**策略类**。策略的创建由工厂类来完成，封装策略创建的细节。策略模式包含一组策略可选，客户端代码如何选择使用哪个策略，有两种确定方法：**编译时静态确定和运行时动态确定**。其中，“**运行时动态确定**”才是策略模式最典型的应用场景。



## 应用场景：

- 一个系统需要动态地在几种算法中选择一种，可以将这些算法封装到具体算法类中，它们都是一个抽象算法类的子类。
- 转移一个对象中行为选择的多重条件选择语句到具体策略类里面，避免使用难以维护的多重条件选择语句。
- 将算法以及复杂的、与算法相关的数据结构封装到具体策略类中，让客户端感知不到提高算法的保密性与安全性。



## 优点：

- 符合开闭原则，策略模式易于扩展，可以在不修改原有系统的基础上选择算法或行为，也可以灵活地增加新的算法或行为。并为算法族提供一种管理机制和维护机制
- 策略模式提供了一种算法的复用机制，客户端可以无差别地通过公共接口调用，利用里式替换原则，灵活使用不同的算法策略；避免了多重条件选择语句的使用

## 缺点：

- 客户端需要知道所有的策略，并在适当的时候选择恰当的算法；
- 会产生很多具体策略类，增加了系统中类的数量；
- 客户端在同一时间只能使用一种策略，无法使用多个策略类。



# 模式结构

## 角色

- **Context（上下文类）** ：环境类是使用算法的角色，在解决某个问题时可以采用多种策略，通过对抽象策略类的引用实例定义所采用的策略。
- **Strategy（抽象策略类）**：声明所支持的算法的抽象方法，可以是抽象类或具体类，也可以是接口，是所有具体策略类的父类。
- **ConcreteStrategy（具体策略类）**：实现了在抽象策略类中声明的算法。

## 类图



![设计模式之策略模式](\upload\设计模式之策略模式\设计模式之策略模式.jpg)

# 代码示例

策略模式，通过选择不同的排序策略对数据排序

Context（上下文类）：Context

Strategy（抽象策略类）： Sort

ConcreteStrategy（具体策略类）： BubbleSort、SelectionSort、InsertionSort



## GitHub



## Context（上下文类）

```cpp
/// Context（上下文类）：Context
class Context {
public:
    Context() {
        sortStrategy = nullptr;
        arr = nullptr;
        len = 0;
        std::cout << "Context Hello" << std::endl;
    }
    ~Context() {
        delete sortStrategy;
        std::cout << "Context Bye" << std::endl;
    }
    void setSortStrategy(Sort* sort){
        delete sortStrategy;
        sortStrategy = sort;
    }
    void sort(){
        sortStrategy->sort(arr, len);
        std::cout << "输出：" << std::endl;
        printSortedArr();
    }
    void setSortArr(int arr[], int len){
        this->arr = arr;
        this->len = len;
    }

    void printSortedArr(){
        std::string arrString;
        for (int i = 0; i < len; i++){
            arrString  += std::to_string(arr[i]) + " ";
        }
        std::cout << arrString <<std::endl;
    }

private:

    Sort* sortStrategy;
    int* arr;
    int len;
};
```



## Strategy（抽象策略类）

```cpp
/// Strategy（抽象策略类）： Sort
class Sort {
public:
    virtual ~Sort() = default;
    virtual void sort(int arr[], int len) = 0;
protected:
    Sort() = default;
};
```



## ConcreteStrategy（具体策略类）

```cpp
/// ConcreteStrategy（具体策略类）： BubbleSort、SelectionSort、InsertionSort
class BubbleSort : public Sort {
public:
    BubbleSort() {
        std::cout << "BubbleSort Hello" << std::endl;
    }
    ~BubbleSort() override {
        std::cout << "BubbleSort Bye" << std::endl;
    }
    /**冒泡排序
       1 比较相邻的元素。如果第一个比第二个大，就交换它们两个；
       2 对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对，这样在最后的元素应该会是最大的数；
       3 针对所有的元素重复以上的步骤，除了最后一个；
       4 重复步骤1~3，直到排序完成。
     */
    /// 待排序区间 分  有序区间 无序区间， 每次循环从无序区间中两两比较并交换位置，将最大（最小）冒出来，放入有序区间
    void sort(int arr[], int len) override { // 冒泡排序
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) { // 比较相邻的元素
                    auto temp = arr[j+1];        // 元素交换
                    arr[j+1] = arr[j];
                    arr[j] = temp;
                }
            }

        }
    }
};


class SelectionSort : public Sort {
public:
    SelectionSort() {
        std::cout << "SelectionSort Hello" << std::endl;
    }
    ~SelectionSort() override {
        std::cout << "SelectionSort Bye" << std::endl;
    }
    /**选择排序
        1 初始状态：无序区为R[1..n]，有序区为空；
        2 第i趟排序(i=1,2,3…n-1)开始时，当前有序区和无序区分别为R[1..i-1]和R(i..n）。
        该趟排序从当前无序区中-选出关键字最小的记录 R[k]，将它与无序区的第1个记录R交换，
        使R[1..i]和R[i+1..n)分别变为记录个数增加1个的新有序区和记录个数减少1个的新无序区；
        3 n-1趟结束，数组有序化了。
     */
    /// 待排序区间 分  有序区间 无序区间， 每次循环从无序区间找出最小数据插入有序区间尾部
    void sort(int arr[], int len) override { // 选择排序 从小到大排序
        int minIndex;
        for (int i = 0; i < len - 1; ++i) {
            minIndex = i;
            for (int j = i + 1; j < len; ++j) { // 无序区
                if (arr[j] < arr[minIndex]) {
                    minIndex = j; // 找最小
                }
            }
            auto temp = arr[i]; // 交换
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
};


class InsertionSort : public Sort {
public:
    InsertionSort() {
        std::cout << "InsertionSort Hello" << std::endl;
    }
    ~InsertionSort() override {
        std::cout << "InsertionSort Bye" << std::endl;
    }
    /**插入排序
        1 从第一个元素开始，该元素可以认为已经被排序；
        2 取出下一个元素，在已经排序的元素序列中从后向前扫描；
        3 如果该元素（已排序）大于新元素，将该元素移到下一位置；
        4 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置；
        5 将新元素插入到该位置后；
        6 重复步骤2~5。
     */
    /// 待排序区间 分  有序区间 无序区间， 每次循环取无序区间第一个数据，在有序区间比较找到插入位置
    void sort(int arr[], int len) override { // 插入排序  从小到大排序
        int current;
        for (int i = 0; i < len - 1; i++) { // 从第一个元素开始
            current = arr[i + 1]; // 取出下一个元素 待排序
            int preIndex = i; // 已排序 最后一个元素
            while (preIndex >= 0 && arr[preIndex] > current ) { //  已排序大于待排序元素current，说明 current 在 arr[preIndex] 前面
                arr[preIndex + 1] = arr[preIndex]; // 移位 留出 插入位置
                preIndex--; // 从后向前扫描
            }
            arr[preIndex + 1] = current; // 插入
        }
    }
};
```



## 测试

```cpp
int main() {
    auto* ctx = new Context();
    // 冒泡排序
    std::cout << "==========冒泡排序：==========" << std::endl;
    int arr1[] = { 3,40,-1,-45,44,56,9,-33 };
    ctx->setSortArr(arr1, sizeof(arr1)/sizeof(int));
    std::cout << "输入：" << std::endl;
    ctx->printSortedArr();
    ctx->setSortStrategy(new BubbleSort());
    ctx->sort();

    // 选择排序
    std::cout << "==========选择排序：==========" << std::endl;
    int arr2[] = { 13,4,-11,-5,14,6,9,-3 };
    ctx->setSortArr(arr2, sizeof(arr2)/sizeof(int));
    std::cout << "输入：" << std::endl;
    ctx->printSortedArr();
    ctx->setSortStrategy(new SelectionSort());
    ctx->sort();

    // 插入排序
    std::cout << "==========插入排序：==========" << std::endl;
    int arr3[] = { 30,-40,1,45,-4,1,-9,3 };
    ctx->setSortArr(arr3, sizeof(arr3)/sizeof(int));
    std::cout << "输入：" << std::endl;
    ctx->printSortedArr();
    ctx->setSortStrategy(new InsertionSort());
    ctx->sort();

    delete ctx;
    return 0;
}
```



## 输出

![image-20210112133635672](\upload\设计模式之策略模式\A_设计模式之策略模式.png)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

