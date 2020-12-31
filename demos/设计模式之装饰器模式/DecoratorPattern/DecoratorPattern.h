//
// Created by leacock on 2020/12/31.
//

#ifndef DECORATORPATTERN_DECORATORPATTERN_H
#define DECORATORPATTERN_DECORATORPATTERN_H

#include <iostream>
#include <iomanip>
#include <sstream>

enum TYPE {
    Base3 = 3,
    Base5 = 5,
};

/// Component（抽象构件）： HandPancake
class HandPancake {
public:
    virtual ~HandPancake() = default;
    virtual std::string offerHandPancake() = 0; // 制作手抓饼
    virtual float calcPrice() = 0; // 计算价格
protected:
    HandPancake() = default;
};

/// ConcreteComponent（具体构件）： ConcreteHandPancake
class ConcreteHandPancake : public HandPancake {
public:
    explicit ConcreteHandPancake(TYPE price) {
        std::cout << "ConcreteHandPancake Hello" << std::endl;
        basePrice = price;
    }
    ~ConcreteHandPancake() override {
        std::cout << "ConcreteHandPancake Bye" << std::endl;
    }
    std::string offerHandPancake() override {
        std::stringstream buf;
        buf.precision(2);//覆盖默认精度
        buf.setf(std::ios::fixed);//保留小数位自动补0
        buf << basePrice;
        std::string str;
        str = buf.str();

        return "基础"+ str + "元手抓饼" ;
    }
    float calcPrice() override {
        return basePrice;
    }

private:
    float basePrice;
};


/// Decorator（抽象装饰类）：Decorator
class Decorator : public HandPancake {
public:
    explicit Decorator(HandPancake *handPancake) {
        this->handPancake = handPancake;
    }
    ~Decorator() override {
        delete handPancake;
    };

    std::string offerHandPancake() override {
        return handPancake->offerHandPancake();
    }
    float calcPrice() override {
        return handPancake->calcPrice();
    }

private:
    HandPancake *handPancake; // 维持一个对抽象构件对象的引用
};

/// ConcreteDecorator（具体装饰类）：addEgg ,  addSausage , addVegetable ,
class addEgg : public Decorator {
public:
    explicit addEgg(HandPancake *handPancake): Decorator(handPancake) {
        std::cout << "addEgg Hello" << std::endl;
    };
    ~addEgg() override {
        std::cout << "addEgg Bye" << std::endl;
    }
    std::string offerHandPancake() override {
        return Decorator::offerHandPancake() + ",加了鸡蛋";
    }
    float calcPrice() override {
        return Decorator::calcPrice() + float(1.5);
    }
};

class addSausage : public Decorator {
public:
    explicit addSausage(HandPancake *handPancake): Decorator(handPancake) {
        std::cout << "addSausage Hello" << std::endl;
    };
    ~addSausage() override {
        std::cout << "addSausage Bye" << std::endl;
    }
    std::string offerHandPancake() override {
        return Decorator::offerHandPancake() + ",加了火腿肠";
    }
    float calcPrice() override {
        return Decorator::calcPrice() + 1;
    }
};

class addVegetable : public Decorator {
public:
    explicit addVegetable(HandPancake *handPancake): Decorator(handPancake) {
        std::cout << "addVegetable Hello" << std::endl;
    };
    ~addVegetable() override {
        std::cout << "addVegetable Bye" << std::endl;
    }
    std::string offerHandPancake() override {
        return Decorator::offerHandPancake() + ",加了青菜";
    }
    float calcPrice() override {
        return Decorator::calcPrice() + float(0.5);
    }
};

/// Customer 顾客
class Customer {
public:
    explicit Customer(const std::string& name) {
        this->name = name;
        std::cout << "Customer " << name <<" Hello" << std::endl;
    }
    ~Customer() {
        delete handPancake;
        std::cout << "Customer " << name <<" Bye" << std::endl;
    }
    void buy(HandPancake *pancake) {
        this->handPancake = pancake;
        // std::setiosflags(std::ios::fixed) << std::setprecision(2)  控制浮点型小数点后输出的位数并自动补0
        std::cout << name + "购买了:" << pancake->offerHandPancake()
                  << ",共花了:" << std::setiosflags(std::ios::fixed) << std::setprecision(2) << pancake->calcPrice() << "元钱" << std::endl;
    }

private:
    std::string name;
    HandPancake *handPancake = nullptr;
};

#endif //DECORATORPATTERN_DECORATORPATTERN_H
