//
// Created by leacock on 2020/12/31.
//

#ifndef FACADEPATTERN_FACADEPATTERN_H
#define FACADEPATTERN_FACADEPATTERN_H

#include <iostream>

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


#endif //FACADEPATTERN_FACADEPATTERN_H
