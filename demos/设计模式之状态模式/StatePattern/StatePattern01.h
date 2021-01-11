//
// Created by leacock on 2021/1/11.
//

#ifndef STATEPATTERN_STATEPATTERN01_H
#define STATEPATTERN_STATEPATTERN01_H

#include <iostream>

enum ScreenState{ mormal_state,  double_state,  quadruple_state};

/// State（抽象状态类）： State
class State{
public:
    virtual ~State() = default;
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




#endif //STATEPATTERN_STATEPATTERN01_H
