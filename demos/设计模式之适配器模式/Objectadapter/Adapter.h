//
// Created by leacock on 2020/12/29.
//

#ifndef CLASSADAPTER_ADAPTER_H
#define CLASSADAPTER_ADAPTER_H

#include <iostream>

/// Target（目标抽象类）
class FilterTarget {
public:
    virtual ~FilterTarget() = default;
    virtual void filter(std::string text) = 0;

protected:
    FilterTarget() = default;
};

/// Adaptee（适配者类）
class FilterAdaptee_A {
public:
    FilterAdaptee_A() {
        std::cout << "FilterAdaptee_A Hello" << std::endl;
        type = "FilterAdaptee_A";
    }
    ~FilterAdaptee_A() {
        std::cout << "FilterAdaptee_A Bye" << std::endl;
    }
    void adapteeFilter(const char *text) {
        std::cout <<"过滤器为：" << type << std::endl;
        std::cout <<"过滤内容为：" << text << std::endl;
    }

private:
    std::string type;
};

class FilterAdaptee_B {
public:
    FilterAdaptee_B() {
        std::cout << "FilterAdaptee_B Hello" << std::endl;
        type = "FilterAdaptee_B";
    }
    ~FilterAdaptee_B() {
        std::cout << "FilterAdaptee_B Bye" << std::endl;
    }
    void adapteeFilter(const std::string& text, const std::string& mask) {
        std::cout <<"过滤器为：" << type << std::endl;
        std::cout <<"过滤内容为：" << text << std::endl;
        std::cout <<"过滤mask为：" << mask << std::endl;

    }

private:
    std::string type;
};



/// Adapter（适配器类）
class FilterAdapter_A: public FilterTarget {
public:
    FilterAdapter_A() {
        std::cout << "Object FilterAdapter_A Hello" << std::endl;
    }
    ~FilterAdapter_A() override {
        std::cout << "Object FilterAdapter_A Bye" << std::endl;
    }

    void filter(const std::string text) override {
        const char *temp = text.c_str();
        filterAdapteeA.adapteeFilter(temp); // 委托
    }

private:
    FilterAdaptee_A filterAdapteeA;
};

class FilterAdapter_B: public FilterTarget {
public:
    FilterAdapter_B() {
        std::cout << "Object FilterAdapter_B Hello" << std::endl;
        mask = "MASK_B";
    }
    ~FilterAdapter_B() override {
        std::cout << "Object FilterAdapter_B Bye" << std::endl;
    }

    void filter(const std::string text) override {
        filterAdapteeB.adapteeFilter(text,mask);
    }

private:
    FilterAdaptee_B filterAdapteeB;
    std::string mask;
};

#endif //CLASSADAPTER_ADAPTER_H
