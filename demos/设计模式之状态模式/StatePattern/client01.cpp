#include "StatePattern01.h"

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
