//
// Created by leacock on 2021/1/11.
//

#ifndef STATEPATTERN_STATEPATTERN02_H
#define STATEPATTERN_STATEPATTERN02_H

#include <iostream>

enum ScreenState{ mormal_state,  double_state,  quadruple_state};

class Screen;

/// State（抽象状态类）： State
class State{
public:
    virtual ~State() = default;
    virtual void changeState(Screen *screen) = 0;
    virtual void display() = 0;
protected:
    State() = default;
};

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

#endif //STATEPATTERN_STATEPATTERN02_H
