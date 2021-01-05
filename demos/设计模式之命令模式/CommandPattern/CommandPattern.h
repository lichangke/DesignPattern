//
// Created by leacock on 2021/1/5.
//

#ifndef COMMANDPATTERN_COMMANDPATTERN_H
#define COMMANDPATTERN_COMMANDPATTERN_H
#include <iostream>
#include <vector>

/// Command（抽象命令类）： Command

class Command {
public:
    virtual ~Command() = default;
    // 声明抽象接口：执行命令
    virtual void execute() = 0;
protected:
    Command() = default;
};

/// Receiver（接收者）： Lamp 、 Fan
class Lamp {
public:
    Lamp() {
        lampState = false;
        std::cout << "Lamp Hello" << std::endl;
    }
    ~Lamp() {
        std::cout << "Lamp Bye" << std::endl;
    }

    void lampOn() {
        lampState = true;
        std::cout << "Lamp On" << std::endl;
    }
    void lampOff() {
        lampState = false;
        std::cout << "Lamp Off" << std::endl;
    }

    bool getLampState(){
        return lampState;
    }
private:
    bool lampState;
};

class Fan {
public:
    Fan() {
        fanState = false;
        std::cout << "Fan Hello" << std::endl;
    }
    ~Fan() {
        std::cout << "Fan Bye" << std::endl;
    }

    void fanOn() {
        fanState = true;
        std::cout << "Fan On" << std::endl;
    }
    void fanOff() {
        fanState = false;
        std::cout << "Fan Off" << std::endl;
    }

    bool getFanState(){
        return fanState;
    }
private:
    bool fanState;
};

/// ConcreteCommand（具体命令类）：  LampCommand 、 FanCommand
class LampCommand : public Command {
public:
    LampCommand() {
        std::cout << "LampCommand Hello" << std::endl;
        lamp = new Lamp();
    }
    ~LampCommand() override {
        std::cout << "LampCommand Bye" << std::endl;
        delete lamp;
    }

    void execute() override{
        if(lamp->getLampState()) { // true
            lamp->lampOff(); // false
        } else {
            lamp->lampOn();
        }
    }

private:
    Lamp *lamp;
};

class FanCommand : public Command {
public:
    FanCommand() {
        std::cout << "FanCommand Hello" << std::endl;
        fan = new Fan();
    }
    ~FanCommand() override {
        std::cout << "FanCommand Bye" << std::endl;
        delete fan;
    }

    void execute() override{
        if(fan->getFanState()) { // true
            fan->fanOff(); // false
        } else {
            fan->fanOn();
        }
    }

private:
    Fan *fan;
};

/// Invoker（调用者）：Switch
class Switch {
public:
    Switch() {
        std::cout << "Switch Hello" << std::endl;
        command = nullptr;
    }
    ~Switch() {
        std::cout << "Switch Bye" << std::endl;
        delete command;
    }
    // 设值注入具体命令类对象
    void setCommand(Command *cmd){
        delete command;// 删除之前命令
        command = cmd;
    }
    // 发送命令：切换开关
    void touch(){
        std::cout << "切换开关:" << std::endl;
        command->execute();
    }
private:
    Command *command;
};


/// CommandVector 命令集合 示例
class CommandVector {
public:
    CommandVector() {
        std::cout << "CommandVector Hello" << std::endl;
    }
    ~CommandVector() {
        std::cout << "CommandVector Bye" << std::endl;
        for(auto command : commandVector) {
            delete command;
        }
    }

    void addCommand(Command *cmd) {
        commandVector.push_back(cmd);
    }

    void execute() { // 直接调用 commandVector 中元素 的 execute
        for(auto command : commandVector) {
            command->execute();
        }
    }
private:
    std::vector<Command *> commandVector;
};

/// Invoker（调用者）：SwitchVector 处理 CommandVector 命令集合
class SwitchVector {
public:
    SwitchVector() {
        std::cout << "SwitchVector Hello" << std::endl;
        commandVector = nullptr;
    }
    ~SwitchVector() {
        std::cout << "SwitchVector Bye" << std::endl;
        delete commandVector;
    }
    // 设值注入具体命令类对象
    void setCommandVector(CommandVector *vector){
        commandVector = vector;
    }
    // 发送命令：切换开关
    void touch(){
        if(nullptr!=commandVector) {
            std::cout << "切换开关:" << std::endl;
            commandVector->execute();
        } else {
            std::cout << "commandVector 为空" << std::endl;
        }

    }
private:
    CommandVector *commandVector;
};

#endif //COMMANDPATTERN_COMMANDPATTERN_H
