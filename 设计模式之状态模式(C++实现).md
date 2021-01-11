更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

[TOC]

# 介绍

状态模式可以看成状态机的一种实现方式。状态机又叫有限状态机，由 3 个部分组成：**状态、事件、动作**。其中，事件也称为转移条件。事件触发状态的转移及动作的执行。不过，动作不是必须的，也可能只转移状态，不执行任何动作。

在软件系统中，有些对象像水一样具有多种状态，这些状态在某些情况下能够相互转换，而且对象在不同的状态下也将具有不同的行为。

## 意图：

**状态模式(State Pattern)：**  允许一个对象在其内部状态改变时改变它的行为，对象看起来似乎修改了它的类。其别名为状态对象(Objects for States)，状态模式是一种对象行为型模式。

## 解决问题：

**状态模式将一个对象的状态从对象中分离出来，封装到专门的状态类中**，解决系统中复杂对象的状态转换以及不同状态下行为的封装问题。

## 实现概述：

### 状态机有三种实现方式

针对**状态机有三种实现方式：利用分支逻辑、查表法、状态模式**

#### 利用 if-else 或者 switch-case 分支逻辑：  

利用 if-else 或者 switch-case 分支逻辑。参照状态转移图，将每一个状态转移原模原样地直译成代码。对于简单的状态机来说，这种实现方式最简单、最直接，是首选。但是这样代码会包含大量的 if-else 或 switch-case 分支判断逻辑，甚至是嵌套的分支判断逻辑。

#### 利用二维数组查表：

对于状态很多、状态转移比较复杂的状态机来说，查表法比较合适。通过二维数组来表示状态转移图，能极大地提高代码的可读性和可维护性。

#### 状态模式：

对于状态并不多、状态转移也比较简单，但事件触发执行的动作包含的业务逻辑可能比较复杂的状态机来说，首选这种实现方式。

### 状态模式实现概述

引入了**抽象状态类**角色，提高系统灵活性和可扩展性，同时对各状态下的共有行为进行封装。

抽象状态类的子类（**具体状态类**）中实现了在抽象状态类中声明的业务方法，不同的具体状态类提供完全不同的方法实现和业务方法。

**环境类** 维持一个对抽象状态类的引用，通过setState()方法可以向环境类注入不同的状态对象，再在环境类的业务方法中调用状态对象的方法。

对象状态之间可以进行相互转换，通常有两种实现状态转换的方式：

 (1) **统一由环境类来负责状态之间的转换** ，此时，环境类还充当了状态管理器(State Manager)角色。通过对某些属性值的判断实现状态转换，还可以提供专门的方法用于实现属性判断和状态转换。

```cpp
void changeState() {
	//判断属性值，根据属性值进行状态转换
	if (value == 0) {
		setState(new ConcreteStateA());
	}
	else if (value == 1) {
		setState(new ConcreteStateB());
	}
	......
}
```

(2) **由具体状态类来负责状态之间的转换**， 可以在**具体状态类**的业务方法中判断**环境类**的某些属性值再根据情况为环境类设置新的状态对象，实现状态转换，也可以提供一个专门的方法来负责属性值的判断和状态转换。

```cpp
void changeState(Context *ctx) {
	//根据环境对象中的属性值进行状态转换
  if (ctx->getValue() == 1) {
		ctx->setState(new ConcreteStateB());
	}
	else if (ctx.getValue() == 2) {
		ctx->setState(new ConcreteStateC());
	}
	......
}
```



## 要点：

抽象状态类和具体状态类是状态模式的核心

## 应用场景：

- 对象的行为依赖于某些属性值也就是它的状态，状态的改变将导致某些行为的变化

- 在代码中包含大量与对象状态有关的条件语句（if-else 或者 switch-case分支逻辑）

## 优点：

- 状态模式**封装了状态转换的规则** ，只给外界暴露了统一的接口，能够对状态转换代码进行集中管理。
- 将所有与某个状态有关的行为**放到一个类中**，只需要注入一个不同的状态对象即可使环境对象拥有不同的行为。
- 允许状态转换逻辑与状态对象合成一体，而不是提供一个巨大的条件语句块，状态模式可以让我们避免使用庞大的条件语句来将业务方法和状态转换代码交织在一起。

## 缺点：

- 状态模式增加了系统中类的个数（不同的具体状态类）
-  状态模式的结构与实现都较为复杂，如果使用不当将导致程序结构和代码的混乱，增加系统设计的难度。
- 增加新的状态类需要修改那些负责状态转换的源代码，对“开闭原则”的支持并不太好。

# 模式结构

## 角色

- **Context（上下文类）**：环境类又称为上下文类，它是拥有多种状态的对象。在上下文类中，维护了一个抽象状态类的实例。上下文类的状态存在多样性，并且在不同的状态下，对象表现出不同的行为。
- **State（抽象状态类）**：用于定义一个接口以封装与环境类的一个特定状态相关的行为，在子类（具体状态类）中实现在各种不同状态对应的方法，其相同的方法可以写在抽象状态类中。
- **ConcreteState（具体状态类）**：抽象状态类的子类，每一个子类实现一个与环境类的一个状态相关的行为，每一个具体状态类对应环境的一个具体状态，不同的具体状态类其行为有所不同。

## 类图

![设计模式之状态模式](\upload\设计模式之状态模式\设计模式之状态模式.jpg)

# 代码示例

屏幕放大镜工具模拟，默认为正常状态，点击一次为二倍大小，再点击一次为四倍大小，如果再次点击变为正常大小。

Context（上下文类）：  Screen 

State（抽象状态类）： State 

ConcreteState（具体状态类）：  NormalState 、DoubleState、QuadrupleState

## GitHub

[StatePattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E7%8A%B6%E6%80%81%E6%A8%A1%E5%BC%8F/StatePattern)



## 环境类来负责状态之间的转换

```cpp
enum ScreenState{ mormal_state,  double_state,  quadruple_state};
```

### Context（上下文类）

```cpp
/// Context（上下文类）：  Screen
class Screen {

public:
    Screen() {
        normalState = new NormalState(); //创建正常状态对象
        doubleState = new DoubleState(); //创建二倍放大状态对象
        quadrupleState = new QuadrupleState(); //创建四倍放大状态对象
        screenState = ScreenState::mormal_state; //设置初始状态
    }

    ~Screen() {
        delete normalState;
        delete doubleState;
        delete quadrupleState;
    }

    //单击事件处理方法，封转了对状态类中 1、业务方法的调用 和 2、状态的转换
    void onClick() {
        std::cout << "点击 click" << std::endl;
        if (screenState == ScreenState::mormal_state) {
            doubleState->display();
            setState(ScreenState::double_state);
        } else if (screenState == ScreenState::double_state) {
            quadrupleState->display();
            setState(ScreenState::quadruple_state);
        } else if (screenState == ScreenState::quadruple_state) {
            normalState->display();
            setState(ScreenState::mormal_state);
        }
    }


private:
    void setState(const ScreenState state) {
        this->screenState = state;
    }

    State  *normalState, *doubleState, *quadrupleState;
    ScreenState screenState;
};
```



### State（抽象状态类）

```cpp
/// State（抽象状态类）： State
class State{
public:
    virtual ~State() = default;
    virtual void display() = 0;
protected:
    State() = default;
};
```



### ConcreteState（具体状态类）

```cpp
/// ConcreteState（具体状态类）：  NormalState 、DoubleState、QuadrupleState
class NormalState : public State {
public:
    NormalState() {
        std::cout << "NormalState Hello" << std::endl;
    }
    ~NormalState() override {
        std::cout << "NormalState Bye" << std::endl;
    }
    void display () override {
        std::cout << "正常大小" << std::endl;
    }
};

class DoubleState : public State {
public:
    DoubleState() {
        std::cout << "DoubleState Hello" << std::endl;
    }
    ~DoubleState() override {
        std::cout << "DoubleState Bye" << std::endl;
    }
    void display () override {
        std::cout << "两倍大小" << std::endl;
    }
};

class QuadrupleState : public State {
public:
    QuadrupleState() {
        std::cout << "QuadrupleState Hello" << std::endl;
    }
    ~QuadrupleState() override {
        std::cout << "QuadrupleState Bye" << std::endl;
    }
    void display () override {
        std::cout << "四倍大小" << std::endl;
    }
};
```



### 测试

```cpp
int main() {
    std::cout << "==环境类来负责状态之间的转换==" << std::endl;
    std::cout << "初始" << std::endl;
    auto *screen = new Screen();
    std::cout << "点击 click 测试" << std::endl;
    screen->onClick();
    screen->onClick();
    screen->onClick();
    screen->onClick();
    screen->onClick();
    delete screen;
    return 0;
}
```



### 输出

![image-20210111173928365](\upload\设计模式之状态模式\A_设计模式之状态模式.png)

## 具体状态类来负责状态之间的转换

```cpp
enum ScreenState{ mormal_state,  double_state,  quadruple_state};
```



### Context（上下文类）

```cpp
/// Context（上下文类）：  Screen
class Screen {

public:
    Screen() {
        normalState = new NormalState();
        doubleState = new DoubleState(); //创建二倍放大状态对象
        quadrupleState = new QuadrupleState(); //创建四倍放大状态对象
        screenState = ScreenState::mormal_state;
        setState(ScreenState::mormal_state);
    }

    ~Screen() {
        delete normalState;
        delete doubleState;
        delete quadrupleState;
    }

    //单击事件处理方法，封转了对状态类中 1、业务方法的调用 和 2、状态的转换
    void onClick() {
        std::cout << "点击 click" << std::endl;
        currentState->changeState(this);
    }

    void setState(const ScreenState &state) {
        screenState = state;
        if (screenState == ScreenState::mormal_state) {
            currentState = normalState;
        } else if (screenState == ScreenState::double_state) {
            currentState = doubleState;
        } else if (screenState == ScreenState::quadruple_state) {
            currentState = quadrupleState;
        }
    }

private:

    State  *currentState= nullptr;
    State  *normalState, *doubleState, *quadrupleState;
    ScreenState screenState;
};
```



### State（抽象状态类）

```cpp
/// State（抽象状态类）： State
class State{
public:
    virtual ~State() = default;
    virtual void changeState(Screen *screen) = 0;
    virtual void display() = 0;
protected:
    State() = default;
};
```



### ConcreteState（具体状态类）

```cpp
/// ConcreteState（具体状态类）：  NormalState 、DoubleState、QuadrupleState
class NormalState : public State {
public:
    NormalState() {
        std::cout << "NormalState Hello" << std::endl;
    }
    ~NormalState() override {
        std::cout << "NormalState Bye" << std::endl;
    }
    void changeState(Screen *screen) override; // class Screen 类后面实现

    void display () override {
        std::cout << "正常大小" << std::endl;
    }
};

class DoubleState : public State {
public:
    DoubleState() {
        std::cout << "DoubleState Hello" << std::endl;
    }
    ~DoubleState() override {
        std::cout << "DoubleState Bye" << std::endl;
    }
    void changeState(Screen *screen) override;
    void display () override {
        std::cout << "两倍大小" << std::endl;
    }
};

class QuadrupleState : public State {
public:
    QuadrupleState() {
        std::cout << "QuadrupleState Hello" << std::endl;
    }
    ~QuadrupleState() override {
        std::cout << "QuadrupleState Bye" << std::endl;
    }
    void changeState(Screen *screen) override;
    void display () override {
        std::cout << "四倍大小" << std::endl;
    }
};

void NormalState::changeState(Screen *screen) {
    display();
    screen->setState(ScreenState::double_state);
}

void DoubleState::changeState(Screen *screen) {
    display();
    screen->setState(ScreenState::quadruple_state);
}

void QuadrupleState::changeState(Screen *screen) {
    display();
    screen->setState(ScreenState::mormal_state);
}
```



### 测试

```cpp
int main() {
    std::cout << "==由具体状态类来负责状态之间的转换==" << std::endl;
    std::cout << "初始" << std::endl;
    auto *screen = new Screen();
    std::cout << "点击 click 测试" << std::endl;
    screen->onClick();
    screen->onClick();
    screen->onClick();
    screen->onClick();
    screen->onClick();
    delete screen;
    return 0;
}
```

### 输出

![image-20210111174057264](\upload\设计模式之状态模式\B_设计模式之状态模式.png)

*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

