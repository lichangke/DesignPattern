#include "BuilderPattern.h"

int main() {

    //指挥者
    Director director;
    //抽象建造者
    AbstractBuilder *builder;
    //产品：套餐
    ProductMeal *house;

    //指定具体建造者A
    builder = new ConcreteBuilderMeal_A();
    director.setBuilder(builder);
    house = director.construct();
    house->showMeal();
    delete builder;
    std::cout << "======================" << std::endl;
    //指定具体建造者C
    builder = new ConcreteBuilderMeal_C();
    director.setBuilder(builder);
    house = director.construct();
    house->showMeal();
    delete builder;
    std::cout << "======================" << std::endl;
    //指定具体建造者B
    builder = new ConcreteBuilderMeal_B();
    director.setBuilder(builder);
    house = director.construct();
    house->showMeal();
    delete builder;

    getchar();
    return 0;
}
