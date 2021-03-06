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
    virtual ~AbstractBallProduct() = default;
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

///具体产品类Football
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

///具体产品类Volleyball
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

/// 定义抽象工厂类
class AbstractFactory
{
public:
    virtual ~AbstractFactory() = default;
    virtual AbstractBallProduct * createProduct() = 0;
protected:
    AbstractFactory() = default;
};

///三个具体工厂类
///具体工厂类  只生产单一产品
class BasketballFactory : public AbstractFactory
{
public:
    BasketballFactory() = default;
    ~BasketballFactory() override {
        std::cout << "BasketballFactory Bye" << std::endl;
    };
    AbstractBallProduct *createProduct() override{
        return  new Basketball();
    }
};

///具体工厂类  只生产单一产品
class FootballFactory : public AbstractFactory
{
public:
    FootballFactory() = default;
    ~FootballFactory() override {
        std::cout << "FootballFactory Bye" << std::endl;
    };
    AbstractBallProduct *createProduct() override{
        return  new Football();
    }
};
///具体工厂类  只生产单一产品
class VolleyballFactory : public AbstractFactory
{
public:
    VolleyballFactory() = default;
    ~VolleyballFactory() override {
        std::cout << "VolleyballFactory Bye" << std::endl;
    };
    AbstractBallProduct *createProduct() override{
        return  new Volleyball();
    }
};

#endif //FACTORYMETHOD_FACTORYMETHOD_H
