更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

[TOC]

# 介绍

中介者模式将一个网状的系统结构变成一个以中介者对象为中心的星形结构，在这个星型结构中，使用中介者对象与其他对象的一对多关系来取代原有对象之间的多对多关系。

## 意图：

**中介者模式(Mediator Pattern)**：用一个中介对象（中介者）来封装一系列的对象交互，中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。中介者模式又称为调停者模式，它是一种对象行为型模式。



## 解决问题：

解决对象与对象之间存在大量的关联关系，导致系统的结构变得很复杂的问题。多个对象类相互耦合，形成了网状结构。

## 实现概述：

核心在于**中介者类**的引入，在中介者模式中，中介者类承担了两方面的职责：

**中转作用（结构性）**：对象与对象之间通过中介者对象中转来发生相互作用，而不需要显式地相互引用。

**协调作用（行为性）**：中介者可以对 对象发来的请求进行进一步处理，

通过**中介者类**将对象间网状结构分离为星型结构。



## 应用场景：

- 系统中对象之间存在**复杂的引用关系**，系统**结构混乱**且难以理解。

- 一个对象引用了其他很多对象，并直接和这些对象交互，导致该对象难以复用。

比如飞机与塔台的关系，每架飞机只跟塔台来通信，发送自己的位置给塔台，由塔台来负责每架飞机的航线调度。



## 优点：

中介者模式可以使对象之间的关系数量急剧减少，通过引入中介者对象，可以将系统的网状结构变成以中介者为中心的星形结构。中介者对象与其他对象的一对多关系取代原有对象之间的多对多关系。对象与对象之间不再直接联系，而是通过中介者对象与另一个对象发生相互作用。简化了对象之间的交互，并使各对象解耦，减少子类生成。

## 缺点：

在具体中介者类中包含了大量对象之间的交互细节，可能导致具体中介者类非常复杂，使得系统难以维护，进而有可能会变成大而复杂的“上帝类”（God Class）。

# 模式结构

- **Mediator（抽象中介者）**：声明一个与各个同事对象之间交互的接口，通常声明一个注册方法，用于增加同事对象；
- **ConcreteMediator（具体中介者）**：抽象中介者的子类，通过协调各个同事对象来实现协作行为，它维持了对各个同事对象的引用。
- **Colleague（抽象同事类）**：声明各个同事类公有的接口，**同时维持了一个对抽象中介者类的引用**；
- **ConcreteColleague（具体同事类）**： 具体实现接口，具体同事类只需与中介者通信，通过中介者完成与其他同事类的通信。

![设计模式之中介者模式](\upload\设计模式之中介者模式\设计模式之中介者模式.jpg)

# 代码示例



Mediator（抽象中介者）:  AbstractChatRoom

ConcreteMediator（具体中介者）: ChatRoom

Colleague（抽象同事类）: Member

ConcreteColleague（具体同事类）: OrdinaryMember、SilverMember



Member关联了ChatRoom，当Member发送消息时，需要经过ChatRoom中介者的处理和转发到指定的Member中。OrdinaryMember普通会员只能发送文字，SilverMember白银会员还能发送图片但是大小有限制，当然还可以加黄金会员、钻石会员等提供其他服务。



## GitHub

[MediatorPattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E4%B8%AD%E4%BB%8B%E8%80%85%E6%A8%A1%E5%BC%8F/MediatorPattern)

## Mediator（抽象中介者）

```cpp
class Member;

class AbstractChatRoom {
public:
    virtual ~AbstractChatRoom() = default;
    virtual void registerMember(Member* member) = 0;
    virtual void sendText(const std::string &from,const std::string &to,const std::string &message) = 0;
    virtual void sendImage(const std::string &from,const std::string &to,const std::string &image) = 0;
protected:
    AbstractChatRoom() = default;
};
```



## ConcreteMediator（具体中介者）

```cpp
/// ConcreteMediator（具体中介者）: ChatRoom
class ChatRoom : public  AbstractChatRoom {
public:
    ChatRoom () {
        std::cout << "ChatRoom Hello" << std::endl;
    }
    ~ChatRoom () override {
        std::cout << "ChatRoom Bye" << std::endl;
    }
    void registerMember(Member* member) override {
        if(!memberMap.count(member->getName())){
            memberMap.insert(make_pair(member->getName(),member));
            member->bindChatroom(this);
        }
    }
    void sendText(const std::string &from,const std::string &to,const std::string &message) override {
        Member *memberTo  = memberMap[to]; // 应该检查 key 是否存在，这里默认存在  下同
        memberTo->receiveText(from,message);
    }
    void sendImage(const std::string &from,const std::string &to,const std::string &image) override {
        Member *memberFrom  = memberMap[from]; // 应该检查 key 是否存在，这里默认存在  下同
        int imageSize = memberFrom->getImageSize(); // 能发送图片的大小
        if(imageSize < image.size()) {
            std::cout << memberFrom->getName() << "无法发送大小超过 " << imageSize << " 的图片,请提升会员等级" << std::endl;
        } else {
            Member *memberTo  = memberMap[to];
            memberTo->receiveImage(from,image);
        }
    }


private:
    std::map<std::string,Member*> memberMap;
};
```



## Colleague（抽象同事类）

```cpp
/// Colleague（抽象同事类）: Member
class Member {
public:
    explicit Member(const std::string &name){
        chatRoom = nullptr;
        imageSize = 0;
        this->name = name;
    }

    std::string getName(){
        return this->name;
    }

    void setName(const std::string &memberName){
        this->name = memberName;
    }

    AbstractChatRoom* getChatroom(){
        return chatRoom;
    }

    void bindChatroom(AbstractChatRoom* pChatRoom){
        this->chatRoom = pChatRoom;
    }

    virtual void sendText(const std::string &to,const std::string &message) = 0;
    virtual void sendImage(const std::string &to,const std::string &image) = 0;

    void receiveText(const std::string& from,const std::string& message){
        std::cout << from << "发送文本给" << this->name << ",内容为:" << message << std::endl;
    }

    void receiveImage(const std::string& from,const std::string& image){
        std::cout << from << "发送图片给" << this->name << ",内容为:" << image << std::endl;
    }
    int getImageSize() {
        return imageSize;
    }

protected:
    AbstractChatRoom *chatRoom;
    std::string name;
    int imageSize; // 图片大小限制， 这里用字符串长度表示
};
```



## ConcreteColleague（具体同事类）

```cpp
/// ConcreteColleague（具体同事类）: OrdinaryMember、SilverMember
class OrdinaryMember : public Member { // 普通会员
public:
    explicit OrdinaryMember(const std::string &name) : Member(name){
        imageSize = 0;
        std::cout << "OrdinaryMember Hello, Name = " << this->name << std::endl;
    }
    ~OrdinaryMember () {
        std::cout << "OrdinaryMember Bye, Name = " << this->name << std::endl;
    }
    void sendText(const std::string &to,const std::string &message) override{
        std::cout << "普通会员发送信息:" << std::endl;
        chatRoom->sendText(name,to,message);
    }

    void sendImage(const std::string &to,const std::string &image) override{
        std::cout << "普通会员不能发送图片!" << std::endl;
    }

};

class SilverMember : public Member { // 白银会员
public:
    explicit SilverMember(const std::string &name) : Member(name){
        imageSize = 8; // 白银会员 图片大小限制为 8
        std::cout << "SilverMember Hello, Name = " << this->name << std::endl;
    }
    ~SilverMember () {
        std::cout << "SilverMember Bye, Name = " << this->name << std::endl;
    }
    void sendText(const std::string &to,const std::string &message) override{
        std::cout << "白银会员发送信息:" << std::endl;
        chatRoom->sendText(name,to,message);
    }

    void sendImage(const std::string &to,const std::string &image) override{
        std::cout << "白银会员发送图片:" << std::endl;
        chatRoom->sendImage(name,to,image);
    }

};
```





## 测试

```cpp
int main() {
    //创建聊天室
    ChatRoom happyChat;

    //创建成员
    OrdinaryMember member1("张三");
    SilverMember member2("李四");

    //注册
    happyChat.registerMember(&member1);
    happyChat.registerMember(&member2);

    //发送信息
    // 张三发送文本
    member1.sendText("李四","李四，你好！");
    // 李四发送文本
    member2.sendText("张三","张三，你好！");

    // 张三发送图片
    member1.sendImage("李四","666.png");

    // 李四发送图片
    member2.sendImage("张三","花.png");
    member2.sendImage("张三","奥利给.png");
    
    return 0;
}
```



## 输出

![image-20210107170759466](\upload\设计模式之中介者模式\A_设计模式之中介者模式.png)

*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

