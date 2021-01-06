更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)



# 介绍

解释器模式描述了如何为简单的语言定义一个文法，如何在该语言中表示一个句子，以及如何解释这些句子。实际上，这里的“语言”不仅仅指我们平时说的中、英、日、法等各种语言。从广义上来讲，只要是能承载信息的载体，都可以称之为“语言”，比如，古代的结绳记事、盲文、哑语、摩斯密码等。



## 意图：

**解释器模式(Interpreter Pattern)：**定义一个语言的文法，并且建立一个解释器来解释该语言中的句子，这里的“语言”是指使用规定格式和语法的代码。解释器模式是一种类行为型模式。



## 解决问题：

如何对信息载体（语言等）进行解释的问题



## 实现概述：

**每个文法规则的语言实例都可以表示为一个抽象语法树**，即每一条具体的语句都可以用抽象语法树来表示。**终结符表达式类的实例作为树的叶子节点，而非终结符表达式类的实例作为非叶子节点，它们可以将终结符表达式类的实例以及包含终结符和非终结符实例的子表达式作为其子节点**。抽象语法树描述了如何构成一个复杂的句子，通过对抽象语法树的分析，可以识别出语言中的终结符类和非终结符类。参见[Redy语法分析－－抽象语法树简介](http://blog.chinaunix.net/uid-26750235-id-3139100.html)

## 要点：

构建语法树，定义终结符与非终结符。

## 应用场景：

-  可以将一个需要解释执行的语言中的句子表示为一个抽象语法树。
- 一些重复出现的问题可以用一种简单的语言进行表达；
- 一个语言的文法较为简单；
- 不考虑执行效率的问题时可以使用解释器模式。

## 优点：

- 易于改变和扩展文法，在解释器中使用类表示语言的文法规则，可以通过继承等机制类改变或扩展文法；
- 每一条文法规则都可以表示为一个类，因此可以方便地实现一个简单的语言；
- 如果要增加新的解释表达式，只需增加一个新的终结符表达式或非终结符表达式类，无需修改原有代码，符合开闭原则。

## 缺点：

- **对于复杂文法难以维护**。由于在解释器模式中每一条规则至少需要定义一个类，因此如果一个语言包含太多文法规则，类的个数将会大量增加，导致系统难以管理和维护；
- 执行效率低，**因为解释器模式中有大量循环和递归调用**。

# 模式结构

- **AbstractExpression（抽象表达式）： ** 声明了抽象的解释操作，它是所有终结符表达式和非终结符表达式的公共父类。
- **TerminalExpression（终结符表达式）：** **终结符是文法规则的组成元素中最基本的语言单位，不能再分解。** 实现了与文法规则中终结符相关的解释操作，句子中的每一个终结符都是该类的一个实例。
-  **NonterminalExpression（非终结符表达式）：** 实现了文法中非终结符的解释操作，非终结符表达式中可以**包含终结符表达式**，也可以继续包含非终结符表达式，因此其解释操作一般通过**递归**的方式来完成。
- **Context（环境类）：** 环境类又称为上下文类，存储解释器之外的一些全局信息，通常它可以临时存储需要解释的语句。



![设计模式之解释器模式](\upload\设计模式之解释器模式\设计模式之解释器模式.jpg)



# 代码示例

解释机器人控制指令（网上很多都用的这个例子ヾ(。￣□￣)ﾂ゜゜゜）

```
说明：
机器人控制程序中包含一些简单的英文控制指令，每一个指令对应一个表达式(expression)，该表达式可以是简单表达式也可以是复合表达式，每一个简单表达式由移动方向(direction)，移动方式(action)和移动距离(distance)三部分组成，其中移动方向包括上(up)、下(down)、左(left)、右(right)；移动方式包括移动(move)和快速移动(run)；移动距离为一个正整数。
 两个表达式之间可以通过与(and)连接，形成复合(composite)表达式。
```
```
文法规则：
expression = direction + action + distance 或 composite //表达式
composite = expression + 'and' + expression //复合表达式
direction = 'up' 或 'down' 或 'left' 或 'right' //移动方向
action = 'move' 或 'run' //移动方式
distance = an integer //移动距离
```

```
终结符（也称为终结符表达式）：direction、action 和 distance，它们是语言的最小组成单位，不能再进行拆分；
非终结符（也称为非终结符表达式），expression 和 composite，它们都是一个完整的句子，包含一系列终结符或非终结符。
```

AbstractExpression（抽象表达式）： AbstractNode

TerminalExpression（终结符表达式）：DirectionNode、ActionNode、DistanceNode

NonterminalExpression（非终结符表达式）：AndNode 、SentenceNode

Context（环境类）：Handler （指令处理类工具类）



## GitHub



[InterpreterPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E8%A7%A3%E9%87%8A%E5%99%A8%E6%A8%A1%E5%BC%8F/InterpreterPattern)



## AbstractExpression（抽象表达式）

```cpp
/// AbstractExpression（抽象表达式）： AbstractNode
class AbstractNode {
public:
    virtual ~AbstractNode() = default;
    virtual std::string interpret() = 0;
protected:
    AbstractNode() = default;
};
```

## TerminalExpression（终结符表达式）

```cpp
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
```

## NonterminalExpression（非终结符表达式）

```cpp
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
```

## Context（环境类）

```cpp
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
```





## 测试

```cpp
int main() {
    {
        std::cout << "=========Test 1 start==========="  << std::endl;
        std::string instruction = "up move 5 and down run 10 and left move 5";
        Handler handler(instruction);
        handler.handle();
        std::cout <<"输入指令: " <<instruction <<std::endl;
        std::cout <<"移动结果：" << handler.output() << std::endl;
        std::cout << "=========Test 1 end==========="  << std::endl;
    }
    std::cout << "--------------------------------"  << std::endl;
    {
        std::cout << "=========Test 2 start==========="  << std::endl;
        std::string instruction = "right run 20 and down move 10 and left run 40 and up run 10";
        Handler handler(instruction);
        handler.handle();
        std::cout <<"输入指令: " <<instruction << std::endl;
        std::cout <<"移动结果：" << handler.output() << std::endl;
        std::cout << "=========Test 2 end==========="  << std::endl;
    }

    return 0;
}
```



## 输出

![image-20210105224120851](\upload\设计模式之解释器模式\A_设计模式之解释器模式.png)

![image-20210105224235252](\upload\设计模式之解释器模式\B_设计模式之解释器模式.png)





*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

