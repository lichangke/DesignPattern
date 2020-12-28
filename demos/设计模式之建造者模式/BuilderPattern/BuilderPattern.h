//
// Created by leacock on 2020/12/28.
//

#ifndef BUILDERPATTERN_BUILDERPATTERN_H
#define BUILDERPATTERN_BUILDERPATTERN_H

#include <iostream>

/// 产品角色（Product）
class ProductMeal {
public:
    ProductMeal() {
        std::cout << "ProductMeal Hello" << std::endl;
    };
    ~ProductMeal() {
        std::cout << "ProductMeal Bye" << std::endl;
    };
    void setBurger(const std::string &iburger) {
        mBurger = iburger;
    }
    void setDrink(const std::string &idrink) {
        mDrink = idrink;
    }
    void setSnacks(const std::string &isnacks) {
        mSnacks = isnacks;
    }

    void showMeal(){
        std::cout << "Burger is " << mBurger << std::endl;
        std::cout << "Drink is " << mDrink << std::endl;
        std::cout << "Snacks is " << mSnacks << std::endl;
    }

private:
    std::string mBurger;
    std::string mDrink;
    std::string mSnacks;
};


/// 抽象建造者（AbstractBuilder）
class AbstractBuilder
{
public:
    virtual ~AbstractBuilder() = default;
    //抽象方法：
    virtual void buildBurger() = 0;
    virtual void buildDrink() = 0;
    virtual void buildSnacks() = 0;
    virtual ProductMeal* getMeal() = 0;

protected:
    AbstractBuilder()= default;

};

/// 具体建造者（ConcreteBuilder）
class ConcreteBuilderMeal_A : public AbstractBuilder{ /// 套餐A
public:
    ConcreteBuilderMeal_A(){
        std::cout << "ConcreteBuilderMeal_A Hello" << std::endl;
        meal = new ProductMeal();
    }
    ~ConcreteBuilderMeal_A() override{
        std::cout << "ConcreteBuilderMeal_A Bye" << std::endl;
        delete meal;
    }
    void buildBurger() override {
        meal->setBurger("Veg Burger");
    };
    void buildDrink() override {
        meal->setDrink("coke");
    }
    void buildSnacks() override {
        meal->setSnacks("French fries");
    }
    ProductMeal* getMeal() override {
        return meal;
    }
private:
    ProductMeal *meal;
};

class ConcreteBuilderMeal_B : public AbstractBuilder{ /// 套餐B
public:
    ConcreteBuilderMeal_B(){
        std::cout << "ConcreteBuilderMeal_B Hello" << std::endl;
        meal = new ProductMeal();
    }
    ~ConcreteBuilderMeal_B() override{
        std::cout << "ConcreteBuilderMeal_B Bye" << std::endl;
        delete meal;
    }
    void buildBurger() override {
        meal->setBurger("Chicken Burger");
    };
    void buildDrink() override {
        meal->setDrink("pepsi");
    }
    void buildSnacks() override {
        meal->setSnacks("Onion rings");
    }
    ProductMeal* getMeal() override {
        return meal;
    }
private:
    ProductMeal *meal;
};
class ConcreteBuilderMeal_C : public AbstractBuilder{ /// 套餐C
public:
    ConcreteBuilderMeal_C(){
        std::cout << "ConcreteBuilderMeal_C Hello" << std::endl;
        meal = new ProductMeal();
    }
    ~ConcreteBuilderMeal_C() override{
        std::cout << "ConcreteBuilderMeal_C Bye" << std::endl;
        delete meal;
    }
    void buildBurger() override {
        meal->setBurger("Veg Burger");
    };
    void buildDrink() override {
        meal->setDrink("cafe");
    }
    void buildSnacks() override {
        meal->setSnacks("French fries");
    }
    ProductMeal* getMeal() override {
        return meal;
    }
private:
    ProductMeal *meal;
};

/// 指挥者（Director）
class Director
{
public:
    Director() {
        std::cout << "Director Hello" << std::endl;
    };
    ~Director() {
        std::cout << "Director Bye" << std::endl;
    }
    //具体实现方法
    void setBuilder(AbstractBuilder *iBuilder){
        this->builder = iBuilder;
    }
    //封装组装流程，返回建造结果
    ProductMeal *construct(){
        builder->buildBurger(); /// 制作顺序
        builder->buildDrink();
        builder->buildSnacks();
        return builder->getMeal();
    }
private:
    AbstractBuilder *builder{};
};

#endif //BUILDERPATTERN_BUILDERPATTERN_H
