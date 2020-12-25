
#include "FactoryMethod.h"

int main() {

    std::cout << "工厂方法模式" << std::endl;
    //定义工厂类对象和产品类对象
    AbstractBallProduct *product = nullptr;
    AbstractFactory *factory = nullptr;

    factory = new BasketballFactory();
    product = factory->createProduct();
    product->productName();
    delete factory;
    delete product;


    factory = new FootballFactory();
    product = factory->createProduct();
    product->productIntroduction();
    delete factory;
    delete product;

    factory = new VolleyballFactory();
    product = factory->createProduct();
    product->productIntroduction();
    delete factory;
    delete product;

    getchar();
    return 0;
}
