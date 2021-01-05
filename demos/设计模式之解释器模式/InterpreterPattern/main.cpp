#include "InterpreterPattern.h"

int main() {


    {
        std::cout << "=========Test 1 start==========="  << std::endl;
        std::string instruction = "up move 5 and down run 10 and left move 5";
        Handler handler(instruction);
        handler.handle();
        std::cout <<"输入指令: " <<instruction <<std::endl;
        std::cout <<"移动结果：" << handler.output() << std::endl;
        std::cout << "=========Test 1 end==========="  << std::endl;
    }
    std::cout << "--------------------------------"  << std::endl;
    {
        std::cout << "=========Test 2 start==========="  << std::endl;
        std::string instruction = "right run 20 and down move 10 and left run 40 and up run 10";
        Handler handler(instruction);
        handler.handle();
        std::cout <<"输入指令: " <<instruction << std::endl;
        std::cout <<"移动结果：" << handler.output() << std::endl;
        std::cout << "=========Test 2 end==========="  << std::endl;
    }

    return 0;
}
