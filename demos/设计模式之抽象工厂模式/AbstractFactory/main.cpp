
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

    delete factory;
    delete phone;
    delete tv;

    factory = new MIFactory();
    phone = factory->createPhone();
    phone->productName();
    tv = factory->createTV();
    tv->productIntroduction();

    delete factory;
    delete phone;
    delete tv;

    getchar();
    return 0;
}
