//
// Created by leacock on 2020/12/24.
//

#ifndef SIMPLEFACTORY_SIMPLEFACTORY_H
#define SIMPLEFACTORY_SIMPLEFACTORY_H

#include <iostream>

///定义抽象产品类
class AbstractBallProduct
{
public:
    virtual ~AbstractBallProduct() = default;
    //抽象方法：
    virtual void productName() = 0;
    virtual void productIntroduction() = 0;
protected:
    AbstractBallProduct()= default;

};

//三个具体产品类
//具体产品类Basketball
class Basketball :public AbstractBallProduct
{
public:
    Basketball() = default;
    ~Basketball() override {
        std::cout << "Basketball Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Basketball" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Basketball" << std::endl;
    }
};

//具体产品类Football
class Football :public AbstractBallProduct
{
public:
    Football() = default;
    ~Football() override {
        std::cout << "Football Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Football" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Football" << std::endl;
    }
};

//具体产品类Volleyball
class Volleyball :public AbstractBallProduct
{
public:
    Volleyball() = default;
    ~Volleyball() override {
        std::cout << "Volleyball Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Volleyball" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Volleyball" << std::endl;
    }
};

/// 定义工厂类和工厂方法
class SimpleFactory
{
public:
    static AbstractBallProduct *getProduct(const std::string& productName)
    {
        AbstractBallProduct *pro = nullptr;
        if (productName == "Basketball"){
            pro = new Basketball();
        }
        else if (productName == "Football"){
            pro = new Football();
        }
        else if (productName == "Volleyball"){
            pro = new Volleyball();
        }
        return pro;
    }
};
#endif //SIMPLEFACTORY_SIMPLEFACTORY_H
