#include "MementoPattern.h"

int main() {

    std::cout << "=====Memento Pattern Start=======" << std::endl;

    ChessPlayer player; // 棋手
    // 左下为 0，0   x 为横轴 y 为竖轴
    ChessMan chessMan1("车",0,0); // 棋子1
    ChessMan chessMan2("马",0,1); // 棋子2

    // 马 前进到 （2，2）
    chessMan2.moveX(2);
    chessMan2.moveY(2);
    player.play(&chessMan2); // 落子

    // 车 前进到 （0，2）
    chessMan1.moveY(2);
    player.play(&chessMan1); // 落子

    // 马 前进到 （3，4）
    chessMan2.moveX(3);
    chessMan2.moveY(4);
    player.play(&chessMan2); // 落子

    // 车 前进到 （1，2）
    chessMan1.moveX(1);
    chessMan1.moveY(2);
    player.play(&chessMan1); // 落子

    std::cout << "============" << std::endl;
    player.undo();// 悔棋  车  （1，2）
    player.undo();// 悔棋  马  （3，4）
    player.redo();// 重做  马  （3，4）  redoStack中还有  车（1，2）

    std::cout << "============" << std::endl;
    // 车 前进到 （3，2）
    chessMan1.moveX(3);
    chessMan1.moveY(2);
    player.play(&chessMan1); // 落子 redoStack中 车（1，2） 被丢弃

    std::cout << "=====Memento Pattern End=======" << std::endl;

    return 0;
}
