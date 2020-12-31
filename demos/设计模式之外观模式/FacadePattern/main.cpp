#include "FacadePattern.h"

int main() {
    std::cout << "=== 外观模式示例 ===" << std::endl;
    auto *powerOnButton = new PowerOnButton();
    powerOnButton->pressButton();
    delete powerOnButton;
    return 0;
}
