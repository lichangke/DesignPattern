
#include "BridgePattern.h"

int main() {

    Shape *shape;
    //绘制 红色 圆形
    std::cout << "=====绘制 红色 圆形=====" << std::endl;
    shape = new Circle();
    shape->chooseColor(new Red());
    shape->showShape();
    delete shape;

    //绘制 绿色 圆形
    std::cout << "=====绘制 绿色 圆形=====" << std::endl;
    shape = new Circle();
    shape->chooseColor(new Green());
    shape->showShape();
    delete shape;

    //绘制 蓝色 矩形
    std::cout << "=====绘制 蓝色 矩形=====" << std::endl;
    shape = new Rectangle();
    shape->chooseColor(new Blue());
    shape->showShape();
    delete shape;

    return 0;
}
