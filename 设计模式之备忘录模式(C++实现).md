更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

[TOC]

# 介绍

备忘录模式也叫快照模式，具体来说，就是在不违背封装原则的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态，以便之后恢复对象为先前的状态。这个模式的定义表达了两部分内容：一部分是，存储副本以便后期恢复；另一部分是，要在不违背封装原则的前提下，进行对象的备份和恢复。

## 意图：

**备忘录模式(Memento Pattern)：** 在不破坏封装的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态，这样可以在以后将对象恢复到原先保存的状态。它是一种对象行为型模式，其别名为Token。

## 解决问题：

主要是用来**防丢失、撤销、恢复**等。它跟平时常说的“备份”很相似。两者的主要区别在于，备忘录模式更**侧重于代码的设计和实现**，备份更**侧重架构设计或产品设计**。

## 实现概述：

应该存在一个原发器类Originator，在真实业务中，原发器类是一个具体的业务类，它包含一些用于存储成员数据的属性。

对于备忘录类Memento而言，它通常提供了与原发器相对应的属性（可以是全部，也可以是部分）用于存储原发器的状态。除了Originator类，不允许其他类来调用备忘录类Memento的构造函数与相关方法。

负责人类Caretaker，它用于保存备忘录对象，并提供getMemento()方法用于向客户端返回一个备忘录对象，原发器通过使用这个备忘录对象可以回到某个历史状态。Caretaker类中不直接调用Memento中的状态改变方法，它的作用仅仅用于存储备忘录对象。

## 要点：

核心是备忘录类以及用于管理备忘录的负责人类的设计。原发器对忘录类拥有控制的权力，负责人只负责管理，而其他类无法访问到备忘录，需要对备忘录进行封装。

## 应用场景：

- 保存一个对象的历史状态（全部状态或部分状态），需要时它能够恢复到先前的状态，实现撤销操作。；
- 防止外界对象破坏一个对象历史状态的封装性，避免将对象历史状态的实现细节暴露给外界对象。

### 生活中场景

下象棋的悔棋

### 软件中场景

文本编辑器中的Ctrl+Z回退，Ctrl+Y重做；

## 优点：

- 提供一种状态恢复的shi'xian'ji实现状态恢复、撤销操作的功能，用户可以恢复到指定的历史状态，让软件系统更加人性化；
- 备忘录封装了信息，除了原生器以外，其他对象访问不了备忘录的代码；备忘录保存了原发器的状态，采用列表、堆栈等集合来存储备忘录对象可以实现多次撤销操作。

## 缺点：

- 资源消耗大。如果需要保存原生器对象的多个历史状态，那么将创建多个备忘录对象；或者如果原生器对象的很多状态都需要保存，也将消耗大量存储资源。

# 模式结构

## 角色

- **Originator（原发器）**： 一个普通类，通过创建一个备忘录类存储当前的内部状态，或者使用备忘录来恢复其内部状态，一般是将系统中需要保存内部状态的类设计为原发器；
- **Memento（备忘录）**： 存储原发器的内部状态。备忘录的设计一般可以参考原发器的设计，根据实际需要确定备忘录类中的属性。 **除了原发器本身与负责人类之外，备忘录对象不能直接供其他类使用**。
- **Caretaker（负责人）**： 负责人又称为管理者，它负责保存备忘录，但是不能对备忘录的内容进行操作或检查。可以存储**一个或多个备忘录对象**，但是只负责保存对象，不能修改对象，也不必知道对象的实现细节。

## 类图

![设计模式之备忘录模式](\upload\设计模式之备忘录模式\设计模式之备忘录模式.jpg)





# 代码示例

模拟象棋悔棋的操作，支持多次悔棋以及撤销悔棋，支持悔棋后重新落子，采用两个栈存储备忘录。

Originator（原发器） ： ChessMan

Memento（备忘录）： ChessMemento

Caretaker（负责人）:  ChessCaretaker

ChessPlayer （棋手）



## GitHub

[MementoPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E5%A4%87%E5%BF%98%E5%BD%95%E6%A8%A1%E5%BC%8F/MementoPattern)

## Originator（原发器）

```cpp
/// Originator（原发器） ： ChessMan
class ChessMan {
public:
    ChessMan(const std::string &type,int x,int y) {
        this->type = type;
        this->x = x;
        this->y = y;
        std::cout << "ChessMan Hello,Type = " << this->type << " X = " << this->x << " Y = " << this->y << std::endl;
    }
    ~ChessMan() {
        std::cout << "ChessMan Bye,Type = " << this->type << " X = " << this->x << " Y = " << this->y << std::endl;
    }

    void moveX(int i) {
        this->x = i;
    }

    void moveY(int i) {
        this->y = i;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    std::string getType() {
        return type;
    }


    //保存状态
    ChessMemento *save() {
        return new ChessMemento(type,x,y);
    }

    //恢复状态
    void restore(ChessMemento *memento) {
        type = memento->getType();
        x = memento->getX();
        y = memento->getY();
    }

private:
    std::string type; // 类型
    int x; // 坐标
    int y; // 坐标

};
```



## Memento（备忘录）

```cpp
/// Memento（备忘录）： ChessMemento
class ChessMemento {
public:
    ChessMemento(const std::string &type,int x,int y) {
        this->type = type;
        this->x = x;
        this->y = y;
        std::cout << "ChessMemento Hello,Type = " << this->type << " X = " << this->x << " Y = " << this->y << std::endl;
    }
    ~ChessMemento() {
        std::cout << "ChessMemento Bye,Type = " << this->type << " X = " << this->x << " Y = " << this->y << std::endl;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    std::string getType() {
        return type;
    }

private:
    std::string type; // 类型
    int x; // 坐标
    int y; // 坐标
};
```



## Caretaker（负责人）

```cpp
/// Caretaker（负责人）:  ChessCaretaker
class ChessCaretaker {
public:
    ChessCaretaker() {
        std::cout << "ChessCaretaker Hello" << std::endl;
    }
    ~ChessCaretaker() {
        std::cout << "ChessCaretaker Bye" << std::endl;
        releaseStack(undoStack);
        releaseStack(redoStack);
    }

    void saveMemento(ChessMemento *memento) { // 表示有新子落下
        undoStack.push(memento);
        releaseStack(redoStack);
    }

    ChessMemento * undoMemento() { // 撤销操作
        ChessMemento *memento = undoStack.top();
        undoStack.pop();
        redoStack.push(memento);
        return memento;
    }

    ChessMemento * redoMemento() { // 重做操作
        ChessMemento *memento = redoStack.top();
        redoStack.pop();
        undoStack.push(memento);
        return memento;
    }

    ChessMemento * showCurrent() { // 展示当前棋子
        ChessMemento *memento = undoStack.top();
        return memento;
    }

private:
    static void releaseStack(std::stack<ChessMemento *> &stack) {
        while (!stack.empty())
        {
            delete stack.top();
            stack.pop();
        }
    }
    std::stack<ChessMemento *> undoStack; // 撤销操作 读取栈
    std::stack<ChessMemento *> redoStack; // 重做操作 读取栈， 撤销后又重新落子 此栈清空

};
```



## ChessPlayer （棋手）

```cpp
/// ChessPlayer （棋手）
class ChessPlayer {
public:
    ChessPlayer() {
        std::cout << "ChessPlayer Hello" << std::endl;
    }
    ~ChessPlayer() {
        std::cout << "ChessPlayer Bye" << std::endl;
    }
    // 下棋
    void play(ChessMan *chess) {
        std::cout << "棋手落子" << std::endl;
        ChessMemento *chessMemento = chess->save();
        chessCaretaker.saveMemento(chessMemento);
        printChess(chessMemento);
    }
    // 悔棋
    void undo() {
        std::cout << "棋手悔棋" << std::endl;
        ChessMemento *chessMemento = chessCaretaker.undoMemento();
        printChess(chessMemento);
    }
    // 重做
    void redo() {
        std::cout << "棋手重做" << std::endl;
        ChessMemento *chessMemento = chessCaretaker.redoMemento();
        printChess(chessMemento);
    }
private:
    static void printChess(ChessMemento *memento) {
        std::cout << "棋子" <<  memento->getType() << "当前位置为：" << " x = "
        << memento->getX() << " y = "<< memento->getY() << std::endl;
    }
    ChessCaretaker chessCaretaker;
};
```



## 测试

```cpp

int main() {

    std::cout << "=====Memento Pattern Start=======" << std::endl;

    ChessPlayer player; // 棋手
    // 左下为 0，0   x 为横轴 y 为竖轴
    ChessMan chessMan1("车",0,0); // 棋子1
    ChessMan chessMan2("马",0,1); // 棋子2

    // 马 前进到 （2，2）
    chessMan2.moveX(2);
    chessMan2.moveY(2);
    player.play(&chessMan2); // 落子

    // 车 前进到 （0，2）
    chessMan1.moveY(2);
    player.play(&chessMan1); // 落子

    // 马 前进到 （3，4）
    chessMan2.moveX(3);
    chessMan2.moveY(4);
    player.play(&chessMan2); // 落子

    // 车 前进到 （1，2）
    chessMan1.moveX(1);
    chessMan1.moveY(2);
    player.play(&chessMan1); // 落子

    std::cout << "============" << std::endl;
    player.undo();// 悔棋  车  （1，2）
    player.undo();// 悔棋  马  （3，4）
    player.redo();// 重做  马  （3，4）  redoStack中还有  车（1，2）

    std::cout << "============" << std::endl;
    // 车 前进到 （3，2）
    chessMan1.moveX(3);
    chessMan1.moveY(2);
    player.play(&chessMan1); // 落子 redoStack中 车（1，2） 被丢弃

    std::cout << "=====Memento Pattern End=======" << std::endl;

    return 0;
}
```



## 输出

![image-20210108162210637](\upload\设计模式之备忘录模式\A_设计模式之备忘录模式.png)

![image-20210108162306915](\upload\设计模式之备忘录模式\B_设计模式之备忘录模式.png)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

