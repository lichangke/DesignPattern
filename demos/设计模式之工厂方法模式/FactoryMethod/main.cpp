
#include "FactoryMethod.h"

int main() {

    std::cout << "工厂方法模式" << std::endl;
    //定义工厂类对象和产品类对象
    AbstractBallProduct *product = nullptr;
    AbstractFactory *factory = nullptr;

    factory = new BasketballFactory();
    product = factory->getProduct();
    product->productName();

    factory = new FootballFactory();
    product = factory->getProduct();
    product->productIntroduction();

    factory = new VolleyballFactory();
    product = factory->getProduct();
    product->productIntroduction();

    getchar();
    return 0;
}
