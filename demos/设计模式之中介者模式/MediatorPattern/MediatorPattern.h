//
// Created by leacock on 2021/1/7.
//

#ifndef MEDIATORPATTERN_MEDIATORPATTERN_H
#define MEDIATORPATTERN_MEDIATORPATTERN_H

#include <iostream>
#include <map>

// Mediator（抽象中介者）:  AbstractChatRoom

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

#endif //MEDIATORPATTERN_MEDIATORPATTERN_H
