#include "IteratorPattern.h"

int main() {

    std::vector<std::string> channelvector = { "综合频道", "财经频道", "综艺频道", "体育频道", "电影频道", "电视剧频道", "纪录频道", "科教频道" , "新闻频道"};
    std::string addChannel1 = "社会与法频道", addChannel2 = "少儿频道";
    // 创建电视
    auto *tv = new Television(channelvector);
    // 创建遥控器
    Iterator *tvRemote = tv->createIterator();

    // 注 频道0为 综合频道； 频道1为 财经频道 ；以此类推
    // 选择频道 5
    std::cout << "选择频道 5" << std::endl;
    tvRemote->chooseChannel(5);
    // 遍历电视所有频道
    std::cout << "以选择频道 5 为基础 顺序 遍历所有频道 " << std::endl;
    do {
        tvRemote->nextChannel();
    } while(5!=tvRemote->getChannel());

    std::cout << "添加 2 个补充频道" << std::endl;
    tv->addChannel(addChannel1);
    tv->addChannel(addChannel2);

    // 选择频道 6
    std::cout << "选择频道 6" << std::endl;
    tvRemote->chooseChannel(6);
    // 遍历电视所有频道
    std::cout << "以选择频道 6 为基础 逆序 遍历所有频道 " << std::endl;
    do {
        tvRemote->nextChannel();
    } while(6!=tvRemote->getChannel());

    delete tv;
    delete tvRemote;
    return 0;
}
