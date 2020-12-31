
#include "DecoratorPattern.h"

int main() {

    //有个 张三 的顾客,他要了一个基础3元的手抓饼
    auto *customerA = new Customer("张三");
    customerA->buy(new ConcreteHandPancake(Base3));
    delete customerA;
    std::cout << "================" << std::endl;
    //有个 李四 的顾客,他要了一个基础5元的手抓饼,加鸡蛋
    auto *customerB = new Customer("李四");
    customerB->buy(new addEgg(new ConcreteHandPancake(Base5)));
    delete customerB;
    std::cout << "================" << std::endl;
    //有个 王五 的顾客,他要了一个基础5元的手抓饼,加鸡蛋,加火腿，加青菜。不愧是 钻石王老五
    auto *customerC = new Customer("王五");
    customerC->buy(new addVegetable(new addSausage(new addEgg(new ConcreteHandPancake(Base5)))));
    delete customerC;

    return 0;
}
