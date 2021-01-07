#include "MediatorPattern.h"

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
