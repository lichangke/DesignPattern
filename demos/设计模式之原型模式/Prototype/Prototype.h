//
// Created by leacock on 2020/12/29.
//

#ifndef PROTOTYPE_PROTOTYPE_H
#define PROTOTYPE_PROTOTYPE_H

#include <iostream>

/// 附件类
class Attachment {
public:
    Attachment() {
        std::cout << "Attachment Hello" << std::endl;
    }
    ~Attachment() {
        std::cout << "Attachment Bye" << std::endl;
    }
    void changeName(const std::string &name) {
        nameAtt = name;
    };
    std::string getName() {
        return nameAtt;
    }
private:
    std::string nameAtt; /// 附件名
};

/// 抽象原型类（AbstractPrototype）
class AbstractPrototypeMail {
public:
    virtual ~AbstractPrototypeMail() = default;
    virtual AbstractPrototypeMail *clone() = 0;
    virtual void showMail() = 0;
    virtual void changeTitle(std::string title) = 0;
    virtual void changeSender(std::string sender) = 0;
    virtual void changeRecipients(std::string rec) = 0;
    virtual void changeBody(std::string body) = 0;
    virtual void changeAtt(std::string name) = 0;
protected:
    AbstractPrototypeMail() = default;
};

/// 具体原型类（ConcretePrototype）
class ConcretePrototypeMail : public AbstractPrototypeMail {
public:
    ConcretePrototypeMail(const std::string &title,const std::string &sender,const std::string &rec,const std::string &body, const std::string &nameAtt=""){
        std::cout << "ConcretePrototypeMail Hello" << std::endl;
        mailTitle = title;
        mailSender = sender;
        mailRecipients = rec;
        mailBody = body;
        if (!nameAtt.empty()) {
            mailAtta = new Attachment();
            mailAtta->changeName(nameAtt);
        }
    }
    ~ConcretePrototypeMail() override {
        std::cout << "ConcretePrototypeMail Bye" << std::endl;
        if (mailAtta!= nullptr) {
            delete(mailAtta);
        }
    }
    AbstractPrototypeMail *clone() override {
        auto *newMail = new ConcretePrototypeMail(mailTitle,mailSender,mailRecipients,mailBody,mailAtta->getName());
        return newMail;
    }
    void showMail() override {
        std::cout << "MailTitle: " << mailTitle << std::endl;
        std::cout << "MailSender: " << mailSender << std::endl;
        std::cout << "MailRecipients: " << mailRecipients << std::endl;
        std::cout << "MailBody: " << mailBody << std::endl;
        std::cout << "MailAttachment: " << mailAtta->getName() << std::endl;

    }
    void changeTitle(const std::string title) override {
        mailTitle = title;
    }
    void changeSender(const std::string sender) override {
        mailSender = sender;
    };
    void changeRecipients(const std::string rec) override {
        mailRecipients = rec;
    }
    void changeBody(const std::string body) override {
        mailBody = body;
    }
    void changeAtt(const std::string name) override  {
        if (mailAtta!= nullptr) {
            delete(mailAtta);
        }
        mailAtta = new Attachment();
        mailAtta->changeName(name);
    }

private:
    std::string mailTitle;
    std::string mailSender;
    std::string mailRecipients; /// 按理说 收件人应该有多个 可改为list等其他数据结构，这里采用std::string用于演示
    std::string mailBody;
    Attachment *mailAtta = nullptr;
};

#endif //PROTOTYPE_PROTOTYPE_H
