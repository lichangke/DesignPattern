#include "Prototype.h"

int main() {
    /// 用于复用的初始邮件创建
    auto *originalMail = new ConcretePrototypeMail("original_title","original_sender","original_rec","original_body");
    originalMail->changeAtt("original_attachment");
    std::cout << "originalMail address: "<< originalMail << std::endl;
    originalMail->showMail();
    /// 深拷贝
    std::cout << "====深拷贝====" << std::endl;
    auto *copyMail_A = originalMail->clone();
    copyMail_A->changeTitle("copymail_title");
    copyMail_A->changeSender("copymail_sender");
    copyMail_A->changeRecipients("copymail_rec");
    copyMail_A->changeBody("copymail_body");
    copyMail_A->changeAtt("copymail_attachment");
    std::cout << "====copyMail_A====" << std::endl;
    std::cout << "copyMail_A address: "<< copyMail_A << std::endl;
    copyMail_A->showMail();
    std::cout << "====originalMail====" << std::endl;
    originalMail->showMail();
    delete originalMail;
    delete copyMail_A;
    return 0;
}
