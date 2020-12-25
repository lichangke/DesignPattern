//
// Created by leacock on 2020/12/24.
//

#ifndef FACTORYMETHOD_FACTORYMETHOD_H
#define FACTORYMETHOD_FACTORYMETHOD_H

#include <iostream>

///定义抽象产品类
class AbstractPhoneProduct
{
public:
    virtual ~AbstractPhoneProduct() = default;
    //抽象方法：
    virtual void productName() = 0;
    virtual void productIntroduction() = 0;
protected:
    AbstractPhoneProduct()= default;

};

///2个具体产品类
///具体产品类 HWPhone
class HWPhone :public AbstractPhoneProduct
{
public:
    HWPhone() = default;
    ~HWPhone() override {
        std::cout << "HWPhone Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a HWPhone" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for HWPhone" << std::endl;
    }
};

///具体产品类 MIPhone
class MIPhone :public AbstractPhoneProduct
{
public:
    MIPhone() = default;
    ~MIPhone() override {
        std::cout << "MIPhone Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a MIPhone" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for MIPhone" << std::endl;
    }
};


///定义抽象产品类
class AbstractTVProduct
{
public:
    virtual ~AbstractTVProduct() = default;
    //抽象方法：
    virtual void productName() = 0;
    virtual void productIntroduction() = 0;
protected:
    AbstractTVProduct()= default;

};



///2个具体产品类
///具体产品类 HWTV
class HWTV :public AbstractTVProduct
{
public:
    HWTV() = default;
    ~HWTV() override {
        std::cout << "HWTV Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a HWTV" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for HWTV" << std::endl;
    }
};

///具体产品类 MITV
class MITV :public AbstractTVProduct
{
public:
    MITV() = default;
    ~MITV() override {
        std::cout << "MITV Bye" << std::endl;
    };
    void productName() override{
        std::cout << "This is a MITV" << std::endl;
    }
    void productIntroduction() override{
        std::cout << "Introduction for MITV" << std::endl;
    }
};


/// 定义抽象工厂类
class AbstractFactory
{
public:
    virtual ~AbstractFactory() = default;
    virtual AbstractPhoneProduct * createPhone() = 0;
    virtual AbstractTVProduct * createTV() = 0;
protected:
    AbstractFactory() = default;
};

///两个具体工厂类
///具体工厂类  生产多个产品
class HWFactory : public AbstractFactory
{
public:
    HWFactory() = default;
    ~HWFactory() override {
        std::cout << "HWFactory Bye" << std::endl;
    };
    AbstractPhoneProduct *createPhone() override{
        return  new HWPhone();
    }
    AbstractTVProduct *createTV() override{
        return  new HWTV();
    }
};

///具体工厂类  生产多个产品
class MIFactory : public AbstractFactory
{
public:
    MIFactory() = default;
    ~MIFactory() override {
        std::cout << "MIFactory Bye" << std::endl;
    };
    AbstractPhoneProduct *createPhone() override{
        return  new MIPhone();
    }
    AbstractTVProduct *createTV() override{
        return  new MITV();
    }
};

#endif //FACTORYMETHOD_FACTORYMETHOD_H
