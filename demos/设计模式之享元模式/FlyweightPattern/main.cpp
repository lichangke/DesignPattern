
#include "FlyweightPattern.h"
#include <functional>
int main() {
    ChessPiece *black1,*black2,*black3,*white1,*white2;
    ChessPieceFactory *factory;

    //获取享元工厂对象
    factory = ChessPieceFactory::getInstance();

    //通过享元工厂获取三颗黑子
    black1 = factory->getChessPiece("b");
    black2 = factory->getChessPiece("b");
    black3 = factory->getChessPiece("b");
    std::cout << "两颗黑子是否相同：" << (black1==black2) <<  std::endl;

    //通过享元工厂获取两颗白子
    white1 = factory->getChessPiece("w");
    white2 = factory->getChessPiece("w");
    std::cout << "两颗白子是否相同：" << (white1==white2) <<  std::endl;

    std::vector<Coordinates *> coordinates;
    //std::function<Coordinates *(Coordinates *)> func = [&coordinates](Coordinates *coord ) {
    auto func = [&coordinates](Coordinates *coord ) {
        coordinates.push_back(coord);
        return coord;
    };
    //显示棋子
    black1->display(func(new Coordinates(1,3)));
    black2->display(func(new Coordinates(2,6)));;
    black3->display(func(new Coordinates(4,7)));;
    white1->display(func(new Coordinates(5,8)));;
    white2->display(func(new Coordinates(4,1)));;

    for (auto & coordinate : coordinates) {
        delete coordinate;
    }
    return 0;
}
