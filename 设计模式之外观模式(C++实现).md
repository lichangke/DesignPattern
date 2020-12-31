# 介绍

接口开发中，为了保证接口的可复用性（或者叫通用性），需要将接口尽量设计得细粒度一点，职责单一一点。如果接口的粒度过小，在使用接口开发一个业务功能时，就会导致需要调用 n 多细粒度的接口才能完成。相反，如果接口粒度设计得太大，一个接口返回 n 多数据，要做 n 多事情，就会导致接口不够通用、可复用性、易用性不好。通过一个合理的外观角色，能够比较好地兼容接口的复用性和易用性。

## 意图：

**外观模式：** 为子系统中的一组接口提供一个统一的入口。外观模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。

> Facade Pattern: Provide a unified interface to a set of interfaces in a subsystem. Facade defines a higher-level interface that makes the subsystem easier to use.



## 解决问题：

解决接口的可复用性（通用性）和易用性之间的矛盾；降低子系统与客户端的耦合度。

## 实现概述：

通过引入一个外观角色来简化客户端与子系统之间的交互，为复杂的子系统调用提供一个统一的入口，降低子系统与客户端的耦合度

## 要点：

外观角色的引入，简化客户端与子系统之间交互

## 应用场景：

(1) 提供一个简单入口，来访问一系列复杂的子系统

(2) 解耦客户端程序与多个子系统，减少它们之间的依赖性，从而提高子系统的独立性和可移植性。



举个栗子，周末加个餐，准备吃一顿土豆烧牛肉，如果自己做，需要先得去市场里买牛肉、土豆以及其他配料，买回来得洗好，然后切好，再按着菜谱一步一步做好，最后才能吃上。如果去餐馆，只需要告诉厨师要土豆烧牛肉，厨师就会将菜做好然后端上来，前面自己做的步骤统统不用关心只和厨师说句话就可以了。这里厨师可以看做是外观角色。



## 优点：

- 外观模式使得客户端不必关心子系统组件，减少了与客户端交互的对象的数量，简化了客户端的编程；
- 外观模式降低子系统与客户端的耦合度；
- 子系统的变化并不需要修改客户端，只需要适当修改外观类即可；
- 子系统之间不会相互影响，而且子系统内部变化也不会影响到外观对象。

## 缺点：

- 如果需要增加或者减少子系统，需要修改外观类，**违反开闭原则**；解决方法：引入抽象外观类，客户端可以针对抽象外观类进行编程，对于新的业务需求，不需要修改原有外观类，而对应增加一个新的具体外观类，由新的具体外观类来关联新的子系统对象。
- 不能限制客户端直接与子系统交互，但如果对客户端访问子系统类做太多的限制则减少了可变性和灵活性。

# 模式结构

**Facade（外观角色）：** 外观角色可以知道相关的（一个或者多个）子系统的功能和责任；在正常情况下，它将所有从客户端发来的请求委派到相应的子系统去，传递给相应的子系统对象处理。

**SubSystem（子系统角色）：** 在软件系统中的子系统角色，每一个子系统可以不是一个单独的类，而是一个类的集合，它实现子系统的功能；子系统并不知道外观的存在，对于子系统而言，外观角色仅仅是另外一个客户端而已。

![设计模式之外观模式](\upload\设计模式之外观模式\设计模式之外观模式.jpg)



# 代码示例

模拟电脑开机，电脑开机需要依次启动多个子系统，主板(Motherboard)上电、内存(Memory)自检、CPU运行、硬盘(HardDisk)读取和操作系统(OS)加载。我们将开机按钮(PowerOnButton)作为外观角色。当然喜欢DIY的，可以加个声控系统，实现声控开机。比较上天的可以通过意念控制开机(๑•̀ㅂ•́)و✧。

Facade（外观角色）： PowerOnButton

SubSystem（子系统角色）：Motherboard、Memory、CPU、HardDisk、OS

## GitHub

[FacadePattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E5%A4%96%E8%A7%82%E6%A8%A1%E5%BC%8F/FacadePattern)

## SubSystem（子系统角色）

```cpp
/// SubSystem（子系统角色）：Motherboard、Memory、CPU、HardDisk、OS
//子系统：Motherboard
class Motherboard
{
public:
    Motherboard() {
        std::cout << "Motherboard Hello" << std::endl;
    }
    ~Motherboard() {
        std::cout << "Motherboard Bye" << std::endl;
    }
    void powerOnMotherboard(){
        std::cout << "-----主板上电" << std::endl;
    }
};
//Memory
class Memory
{
public:
    Memory() {
        std::cout << "Memory Hello" << std::endl;
    }
    ~Memory() {
        std::cout << "Memory Bye" << std::endl;
    }
    void selfCheckMemory(){
        std::cout << "-----内存自检电" << std::endl;
    }
};

//CPU
class CPU
{
public:
    CPU() {
        std::cout << "CPU Hello" << std::endl;
    }
    ~CPU() {
        std::cout << "CPU Bye" << std::endl;
    }
    void runCPU(){
        std::cout << "-----CPU运行" << std::endl;
    }
};

//HardDisk
class HardDisk
{
public:
    HardDisk() {
        std::cout << "HardDisk Hello" << std::endl;
    }
    ~HardDisk() {
        std::cout << "HardDisk Bye" << std::endl;
    }
    void readHardDisk(){
        std::cout << "-----读取硬盘" << std::endl;
    }
};

//OS
class OS
{
public:
    OS() {
        std::cout << "OS Hello" << std::endl;
    }
    ~OS() {
        std::cout << "OS Bye" << std::endl;
    }
    void loadOS(){
        std::cout << "-----加载操作系统" << std::endl;
    }
};
```



## Facade（外观角色）



```cpp
/// Facade（外观角色）： PowerOnButton
class PowerOnButton {
public:
    PowerOnButton() {
        std::cout << "PowerOnButton Hello" << std::endl;
        motherBoard = new Motherboard();
        memory = new Memory();
        cpu = new CPU();
        hardDisk = new HardDisk();
        os = new OS();
    }
    ~PowerOnButton() {
        delete os;
        delete hardDisk;
        delete cpu;
        delete memory;
        delete motherBoard;
        std::cout << "PowerOnButton Bye" << std::endl;
    };
    void pressButton(){
        std::cout << "Press PowerOn Button" << std::endl;
        std::cout << "正在开机..." << std::endl;
        std::cout << "...." << std::endl;
        std::cout << ".." << std::endl;
        motherBoard->powerOnMotherboard();
        memory->selfCheckMemory();
        cpu->runCPU();
        hardDisk->readHardDisk();
        os->loadOS();
        printf("开机完成！\n");
    }
private:
    Motherboard *motherBoard = nullptr;
    Memory *memory = nullptr;
    CPU *cpu = nullptr;
    HardDisk *hardDisk = nullptr;
    OS *os = nullptr;

};
```





## 测试

```cpp
int main() {
    std::cout << "=== 外观模式示例 ===" << std::endl;
    auto *powerOnButton = new PowerOnButton();
    powerOnButton->pressButton();
    delete powerOnButton;
    return 0;
}
```



## 输出

![image-20201231163959410](\upload\设计模式之外观模式\A_设计模式之外观模式.png)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

