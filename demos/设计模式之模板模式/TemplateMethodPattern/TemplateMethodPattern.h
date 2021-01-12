//
// Created by leacock on 2021/1/12.
//

#ifndef TEMPLATEMETHODPATTERN_TEMPLATEMETHODPATTERN_H
#define TEMPLATEMETHODPATTERN_TEMPLATEMETHODPATTERN_H

#include <iostream>

/// AbstractClass（抽象类）：OnlineMall
class OnlineMall {
public:
    virtual ~OnlineMall() = default;

    // 算法的流程框架
    void shopping(){ /// 流程大体为：选商品->加购物车->付款
        selectProduct();
        addShoppingCart();
        payment();
    }

protected:
    virtual void selectProduct() = 0; /// 选商品
    virtual void addShoppingCart() = 0; /// 加购物车
    virtual void payment() = 0;  /// 付款

    OnlineMall() = default;
};

/// ConcreteClass（派生类）： TaoBao 、JingDong
class TaoBao : public OnlineMall{
public:
    TaoBao() {
        std::cout << "TaoBao Hello" << std::endl;
    }

    ~TaoBao() override {
        std::cout << "TaoBao Bye" << std::endl;
    }

private:
    void selectProduct() override {
        std::cout << "在 TaoBao 选商品" << std::endl;
    }

    void addShoppingCart() override {
        std::cout << "将商品加入 TaoBao 购物车" << std::endl;
    }

    void payment() override {
        std::cout << "支付 TaoBao 购物车待付款给" << std::endl;
    }
};

class JingDong : public OnlineMall{
public:
    JingDong() {
        std::cout << "JingDong Hello" << std::endl;
    }

    ~JingDong() override {
        std::cout << "JingDong Bye" << std::endl;
    }

private:
    void selectProduct() override {
        std::cout << "在 JingDong 选商品" << std::endl;
    }

    void addShoppingCart() override {
        std::cout << "将商品加入 JingDong 购物车" << std::endl;
    }

    void payment() override {
        std::cout << "支付 JingDong 购物车待付款给" << std::endl;
    }
};


#endif //TEMPLATEMETHODPATTERN_TEMPLATEMETHODPATTERN_H
