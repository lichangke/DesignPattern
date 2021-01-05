//
// Created by leacock on 2021/1/5.
//

#include "CommandPattern.h"

int main() {

    // 实例化调用者：开关 (调用者)
    auto *pSwitchVector = new SwitchVector();
    // (具体命令) ， pSwitchVector 中 析构 会处理 commandVector
    Command *lampCmd, *fanCmd;
    //  命令集合
    auto *commandVector = new CommandVector();

    std::cout << "====CommandVector Test====" << std::endl;
    // 按钮 控制 电灯 Lamp
    lampCmd = new LampCommand(); // 具体命令
    commandVector->addCommand(lampCmd);
    // 按钮控制风扇
    fanCmd = new FanCommand();
    commandVector->addCommand(fanCmd);

    pSwitchVector->setCommandVector(commandVector);

    pSwitchVector->touch(); // 开
    pSwitchVector->touch(); // 关
    pSwitchVector->touch(); // 开

    delete pSwitchVector;

    return 0;
}