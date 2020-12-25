//
// Created by leacock on 2020/12/24.
//

#ifndef FACTORYMETHOD_FACTORYMETHOD_H
#define FACTORYMETHOD_FACTORYMETHOD_H

#include <iostream>

///定义抽象产品类
class AbstractBallProduct
{
public:
    ~AbstractBallProduct() = default;
    //抽象方法：
    virtual void productName() = 0;
    virtual void productIntroduction() = 0;
protected:
    AbstractBallProduct()= default;

};

///三个具体产品类
///具体产品类Basketball
class Basketball :public AbstractBallProduct
{
public:
    Basketball() = default;
    ~Basketball() {
        std::cout << "Basketball Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Basketball" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Basketball" << std::endl;
    }
};

///具体产品类Football
class Football :public AbstractBallProduct
{
public:
    Football() = default;
    ~Football() {
        std::cout << "Football Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Football" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Football" << std::endl;
    }
};

///具体产品类Volleyball
class Volleyball :public AbstractBallProduct
{
public:
    Volleyball() = default;
    ~Volleyball() {
        std::cout << "Volleyball Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a Volleyball" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for Volleyball" << std::endl;
    }
};

/// 定义抽象工厂类
class AbstractFactory
{
public:
    ~AbstractFactory() = default;
    virtual AbstractBallProduct * getProduct() = 0;
protected:
    AbstractFactory() = default;
};

///三个具体工厂类
///具体工厂类  只生产单一产品
class BasketballFactory : public AbstractFactory
{
public:
    BasketballFactory() = default;
    ~BasketballFactory() = default;
    AbstractBallProduct *getProduct() override{
        return  new Basketball();
    }
};

///具体工厂类  只生产单一产品
class FootballFactory : public AbstractFactory
{
public:
    FootballFactory() = default;
    ~FootballFactory() = default;
    AbstractBallProduct *getProduct() override{
        return  new Football();
    }
};
///具体工厂类  只生产单一产品
class VolleyballFactory : public AbstractFactory
{
public:
    VolleyballFactory() = default;
    ~VolleyballFactory() = default;
    AbstractBallProduct *getProduct() override{
        return  new Volleyball();
    }
};

#endif //FACTORYMETHOD_FACTORYMETHOD_H
