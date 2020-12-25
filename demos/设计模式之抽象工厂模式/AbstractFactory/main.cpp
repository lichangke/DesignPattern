
#include "AbstractFactory.h"

int main() {

    std::cout << "抽象工厂模式" << std::endl;
    //定义工厂类对象和产品类对象
    AbstractPhoneProduct *phone = nullptr;
    AbstractTVProduct *tv = nullptr;
    AbstractFactory *factory = nullptr;

    factory = new HWFactory();
    phone = factory->createPhone();
    phone->productName();
    tv = factory->createTV();
    tv->productIntroduction();

    factory = new MIFactory();
    phone = factory->createPhone();
    phone->productName();
    tv = factory->createTV();
    tv->productIntroduction();

    getchar();
    return 0;
}
