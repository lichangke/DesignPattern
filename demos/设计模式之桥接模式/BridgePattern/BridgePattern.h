//
// Created by leacock on 2020/12/30.
//

#ifndef BRIDGEPATTERN_BRIDGEPATTERN_H
#define BRIDGEPATTERN_BRIDGEPATTERN_H

#include <iostream>





/// Implementor（实现类接口）： Color
class Color {
public:
    virtual ~Color() = default;
    virtual void fillColor() = 0;
};

/// ConcreteImplementor（具体实现类）：Red、Green、Blue
class Red : public Color {
public:
    Red() {
        std::cout << "Red Hello" << std::endl;
        colorType = "Red";
    }
    ~Red() override {
        std::cout << "Red Bye" << std::endl;
    }
    void fillColor() override {
        std::cout << "填充颜色： " << colorType << std::endl;
    }

private:
    std::string colorType;
};

class Green : public Color {
public:
    Green() {
        std::cout << "Green Hello" << std::endl;
        colorType = "Green";
    }
    ~Green() override {
        std::cout << "Green Bye" << std::endl;
    }
    void fillColor() override {
        std::cout << "填充颜色： " << colorType << std::endl;
    }

private:
    std::string colorType;
};

class Blue : public Color {
public:
    Blue() {
        std::cout << "Blue Hello" << std::endl;
        colorType = "Blue";
    }
    ~Blue() override {
        std::cout << "Blue Bye" << std::endl;
    }
    void fillColor() override {
        std::cout << "填充颜色： " << colorType << std::endl;
    }

private:
    std::string colorType;
};

/// Abstraction（抽象类） : Shape
class Shape {
public:
    virtual ~Shape() = default;
    virtual void showShape() = 0;
    virtual void chooseColor(Color *col) = 0;
protected:
    virtual void drawShape() = 0;
    virtual void drawColor() = 0;
    Color *color = nullptr;
};

/// RefinedAbstraction（扩充抽象类）：Circle 、Rectangle
class Circle : public Shape {
public:
    Circle() {
        std::cout << "Circle Hello" << std::endl;
        shapeType = "Circle";
    }
    ~Circle() override {
        std::cout << "Circle Bye" << std::endl;
        delete color;
    }
    void showShape() override {
        drawShape();
        drawColor();
    }
    void chooseColor(Color *col) override {
        color = col;
    }
private:
    void drawShape() override {
        std::cout << "绘制图形： " << shapeType << std::endl;
    }
    void drawColor() override {
        color->fillColor();
    }
    std::string shapeType;
};

class Rectangle : public Shape {
public:
    Rectangle() {
        std::cout << "Rectangle Hello" << std::endl;
        shapeType = "Rectangle";
    }
    ~Rectangle() override {
        std::cout << "Rectangle Bye" << std::endl;
        delete color;
    }
    void showShape() override {
        drawShape();
        drawColor();
    }
    void chooseColor(Color *col) override {
        color = col;
    }
private:
    void drawShape() override {
        std::cout << "绘制图形： " << shapeType << std::endl;
    }
    void drawColor() override {
        color->fillColor();
    }
    std::string shapeType;
};

#endif //BRIDGEPATTERN_BRIDGEPATTERN_H
