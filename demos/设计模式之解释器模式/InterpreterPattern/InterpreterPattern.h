//
// Created by leacock on 2021/1/5.
//

#ifndef INTERPRETERPATTERN_INTERPRETERPATTERN_H
#define INTERPRETERPATTERN_INTERPRETERPATTERN_H

#include <iostream>
#include <vector>
#include <cstring>
#include <stack>

/// AbstractExpression（抽象表达式）： AbstractNode
class AbstractNode {
public:
    virtual ~AbstractNode() = default;
    virtual std::string interpret() = 0;
protected:
    AbstractNode() = default;
};

/// TerminalExpression（终结符表达式）：DrectionNode 、ActionNode、DistanceNode
//方向解释：终结符表达式
class DirectionNode : public AbstractNode {
public:
    explicit DirectionNode(const std::string &direction) {
        this->direction = direction;
        std::cout << "DirectionNode, Hello. Direction = " << this->direction << std::endl;
    }
    ~DirectionNode() override {
        std::cout << "DirectionNode, Bye. Direction = " << this->direction << std::endl;
    }

    //方向表达式的解释操作
    std::string interpret() override {
        /// 注 这里未处理 大写 字母， 演示模式 默认 全小写
        if (direction == "up") {
            return "向上";
        } else if (direction == "down") {
            return "向下";
        } else if (direction == "left") {
            return "向左";
        } else if (direction == "right") {
            return "向右";
        } else {
            return "无效指令";
        }

    }
private:
    std::string direction;
};

//动作解释：终结符表达式
class ActionNode : public AbstractNode {
public:
    explicit ActionNode(const std::string &action) {
        this->action = action;
        std::cout << "ActionNode, Hello. Action = " << this->action << std::endl;
    }
    ~ActionNode() override {
        std::cout << "ActionNode, Bye. Action = " << this->action << std::endl;
    }
    //动作（移动方式）表达式的解释操作
    std::string interpret() override {
        if (action == "move") {
            return "移动";
        }
        else if (action == "run") {
            return "快速移动";
        }
        else {
            return "无效指令";
        }
    }

private:
    std::string action;
};
//距离解释：终结符表达式
class DistanceNode : public AbstractNode {
public:
    explicit DistanceNode(const std::string &distance) {
        this->distance = distance;
        std::cout << "DistanceNode, Hello. Distance = " << this->distance << std::endl;
    }
    ~DistanceNode() override {
        std::cout << "DistanceNode, Bye. Distance = " << this->distance << std::endl;
    }
    //距离表达式的解释操作
    std::string interpret() override {
        return distance;
    }

private:
    std::string distance;
};

/// NonterminalExpression（非终结符表达式）：AndNode 、SentenceNode
//And解释：非终结符表达式
class AndNode : public AbstractNode {
public:
    AndNode(AbstractNode *left, AbstractNode *right) {
        this->left = left;
        this->right = right;
        std::cout << "AndNode, Hello." << "left = " << this->left
        << " right = " << this->right << std::endl;
    }
    ~AndNode() override{
        std::cout << "AndNode, Bye." << "left = " << this->left
        << " right = " << this->right << std::endl;
        delete left;
        delete right;
    }

    std::string interpret() override {
        return left->interpret() + "再" + right->interpret();
    }
private:
    AbstractNode *left; //And的左表达式
    AbstractNode *right; //And的右表达式
};
//简单句子解释：非终结符表达式
class SentenceNode : public AbstractNode {
public:
    SentenceNode(AbstractNode *direction, AbstractNode *action, AbstractNode *distance) {
        this->direction = direction;
        this->action = action;
        this->distance = distance;
        std::cout << "SentenceNode, Hello." << "direction = " << this->direction
        << " action = " << this->action << " distance = " << this->distance << std::endl;
    }
    ~SentenceNode() override{
        std::cout << "SentenceNode, Bye." << "direction = " << this->direction
                  << " action = " << this->action << " distance = " << this->distance << std::endl;
        delete direction;
        delete action;
        delete distance;

    }

    std::string interpret() override {
        return direction->interpret() + action->interpret() + distance->interpret();
    }
private:
    AbstractNode *direction; // 移动方向
    AbstractNode *action; // 移动方式
    AbstractNode *distance; // 移动距离
};

///Context（环境类）：Handler  （指令处理类工具类）
class Handler  {
public:
    explicit Handler (const std::string &input) {
        expression = input;
        finalExp = nullptr;
        std::cout << "Handler , Hello: " << expression << std::endl;
    }
    ~Handler () {
        std::cout << "Handler , Bye: " << expression << std::endl;
        delete finalExp;
    }
    void handle() {
        AbstractNode *left = nullptr, *right = nullptr;
        AbstractNode *direction = nullptr, *action = nullptr, *distance = nullptr;

        // 分割 expression 这里 借助strtok实现split， 其他方式自行百度
        char* inputCh = const_cast<char *>(expression.c_str());
        char *token = strtok(inputCh, " ");
        while (token != nullptr){
            expVector.emplace_back(token);
            token = strtok(nullptr, " ");
        }
        for (int i = 0; i < expVector.size(); i++) {
            // 如果遇到and则将其后的三个单词连成一个简单句子（Sentence）作为"and"的右表达式，而将栈顶弹出的表达式作为"and"的左表达式，最后将新的And表达式压入栈中
            if("and" == expVector[i]) { //
                //从弹出栈顶作为and的左表达式
                left = stackExp.top();
                stackExp.pop();

                std::string dir = expVector[++i]; // i 先 +1
                direction = new DirectionNode (dir);
                std::string act = expVector[++i];
                action = new ActionNode(act);
                std::string dis = expVector[++i];
                distance = new DistanceNode(dis);

                //组成一个简单表达式作为And的右表达式
                right = new SentenceNode(direction, action, distance);

                //生成And表达式，并压入栈中
                stackExp.push(new AndNode (left, right));
            } else {
                //如果不是and表达式，就从头开始进行解释，将前3个单词作为Sentence的三个操作数，生成简单表达式解析器后压入栈中
                std::string dir = expVector[i];
                direction = new DirectionNode (dir);
                std::string act = expVector[++i]; // i 先 +1
                action = new ActionNode(act);
                std::string dis = expVector[++i];
                distance = new DistanceNode(dis);

                //组成一个简单表达式作为And的右表达式
                stackExp.push(new SentenceNode(direction, action, distance));
            }
        }
        /// 最后 解释成一条表达式语句并存放在 栈 stackExp中
        if(!stackExp.empty()){
            finalExp = stackExp.top();
            stackExp.pop();
        } else {
            finalExp = nullptr;
        }
    }

    std::string output(){
        return finalExp == nullptr ? "**empty**": finalExp->interpret();
    }

private:
    //声明一个栈对象用于存储抽象语法树
    std::stack<AbstractNode*> stackExp; // 存储表达式的栈
    std::vector<std::string> expVector; // expression 按空格分割后 存储 vector
    std::string expression;
    AbstractNode *finalExp;
};

#endif //INTERPRETERPATTERN_INTERPRETERPATTERN_H
