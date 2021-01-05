#include "CommandPattern.h"

int main() {

    // 实例化调用者：开关 (调用者)
    auto *pSwitch = new Switch();
    // (具体命令) ， Switch 中 函数 setCommand和析构 会处理 命令 Command
    Command *lampCmd, *fanCmd;

    std::cout << "====Lamp Test====" << std::endl;
    // 按钮 控制 电灯 Lamp
    lampCmd = new LampCommand(); // 具体命令
    pSwitch->setCommand(lampCmd);
    pSwitch->touch(); // 开
    pSwitch->touch(); // 关
    pSwitch->touch(); // 开

    std::cout << "====Fan Test====" << std::endl;
    // 按钮控制风扇
    fanCmd = new FanCommand();
    pSwitch->setCommand(fanCmd);
    pSwitch->touch(); // 开
    pSwitch->touch(); // 关
    pSwitch->touch(); // 开
    std::cout << "==============" << std::endl;
    delete pSwitch;
    return 0;
}
