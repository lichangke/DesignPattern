
#include "SimpleFactory.h"

int main() {
    std::cout << "简单工厂模式" << std::endl;
    //定义工厂类对象
    AbstractBallProduct *product = nullptr;
    product = SimpleFactory::getProduct("Basketball");
    product->productName();
    product = SimpleFactory::getProduct("Football");
    product->productIntroduction();
    product = SimpleFactory::getProduct("Volleyball");
    product->productIntroduction();
    getchar();
    return 0;
}
