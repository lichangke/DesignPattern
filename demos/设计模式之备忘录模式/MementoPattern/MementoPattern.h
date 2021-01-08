//
// Created by leacock on 2021/1/8.
//

#ifndef MEMENTOPATTERN_MEMENTOPATTERN_H
#define MEMENTOPATTERN_MEMENTOPATTERN_H

#include <iostream>
#include <stack>


/// Memento（备忘录）： ChessMemento
class ChessMemento {
public:
    ChessMemento(const std::string &type,int x,int y) {
        this->type = type;
        this->x = x;
        this->y = y;
        std::cout << "ChessMemento Hello,Type = " << this->type << " X = " << this->x << " Y = " << this->y << std::endl;
    }
    ~ChessMemento() {
        std::cout << "ChessMemento Bye,Type = " << this->type << " X = " << this->x << " Y = " << this->y << std::endl;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    std::string getType() {
        return type;
    }

private:
    std::string type; // 类型
    int x; // 坐标
    int y; // 坐标
};


/// Originator（原发器） ： ChessMan
class ChessMan {
public:
    ChessMan(const std::string &type,int x,int y) {
        this->type = type;
        this->x = x;
        this->y = y;
        std::cout << "ChessMan Hello,Type = " << this->type << " X = " << this->x << " Y = " << this->y << std::endl;
    }
    ~ChessMan() {
        std::cout << "ChessMan Bye,Type = " << this->type << " X = " << this->x << " Y = " << this->y << std::endl;
    }

    void moveX(int i) {
        this->x = i;
    }

    void moveY(int i) {
        this->y = i;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    std::string getType() {
        return type;
    }


    //保存状态
    ChessMemento *save() {
        return new ChessMemento(type,x,y);
    }

    //恢复状态
    void restore(ChessMemento *memento) {
        type = memento->getType();
        x = memento->getX();
        y = memento->getY();
    }

private:
    std::string type; // 类型
    int x; // 坐标
    int y; // 坐标

};


// Caretaker（负责人）:  ChessCaretaker
class ChessCaretaker {
public:
    ChessCaretaker() {
        std::cout << "ChessCaretaker Hello" << std::endl;
    }
    ~ChessCaretaker() {
        std::cout << "ChessCaretaker Bye" << std::endl;
        releaseStack(undoStack);
        releaseStack(redoStack);
    }

    void saveMemento(ChessMemento *memento) { // 表示有新子落下
        undoStack.push(memento);
        releaseStack(redoStack);
    }

    ChessMemento * undoMemento() { // 撤销操作
        ChessMemento *memento = undoStack.top();
        undoStack.pop();
        redoStack.push(memento);
        return memento;
    }

    ChessMemento * redoMemento() { // 重做操作
        ChessMemento *memento = redoStack.top();
        redoStack.pop();
        undoStack.push(memento);
        return memento;
    }

    ChessMemento * showCurrent() { // 展示当前棋子
        ChessMemento *memento = undoStack.top();
        return memento;
    }

private:
    static void releaseStack(std::stack<ChessMemento *> stack) {
        while (!stack.empty())
        {
            delete stack.top();
            stack.pop();
        }
    }
    std::stack<ChessMemento *> undoStack; // 撤销操作 读取栈
    std::stack<ChessMemento *> redoStack; // 重做操作 读取栈， 撤销后又重新落子 此栈清空

};

/// ChessPlayer （棋手）
class ChessPlayer {
public:
    ChessPlayer() {
        std::cout << "ChessPlayer Hello" << std::endl;
    }
    ~ChessPlayer() {
        std::cout << "ChessPlayer Bye" << std::endl;
    }
    // 下棋
    void play(ChessMan *chess) {
        std::cout << "棋手落子" << std::endl;
        ChessMemento *chessMemento = chess->save();
        chessCaretaker.saveMemento(chessMemento);
        printChess(chessMemento);
    }
    // 悔棋
    void undo() {
        std::cout << "棋手悔棋" << std::endl;
        ChessMemento *chessMemento = chessCaretaker.undoMemento();
        printChess(chessMemento);
    }
    // 重做
    void redo() {
        std::cout << "棋手重做" << std::endl;
        ChessMemento *chessMemento = chessCaretaker.redoMemento();
        printChess(chessMemento);
    }
private:
    static void printChess(ChessMemento *memento) {
        std::cout << "棋子" <<  memento->getType() << "当前位置为：" << " x = "
        << memento->getX() << " y = "<< memento->getY() << std::endl;
    }
    ChessCaretaker chessCaretaker;
};


#endif //MEMENTOPATTERN_MEMENTOPATTERN_H
