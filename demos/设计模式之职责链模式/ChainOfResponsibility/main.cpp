#include "ChainOfResponsibility.h"

int main() {
    // 请求处理者：张三， 李四， 王五， 赵六
    AbstractHandler *level1, *level2, *level3, *level4;

    level1 = new TeamLeader("张三");
    level2 = new Supervisor("李四");
    level3 = new Manager("王五");
    level4 = new Boss("赵六");
    std::cout << "=============== " << std::endl;

    /// 建立职责链的工作是在客户端进行
    level1->setNextHandler(level2);
    level2->setNextHandler(level3);
    level3->setNextHandler(level4);

    // 创建单据
    Bill *bill1 = new Bill(1, "Bill_1", 8);
    Bill *bill2 = new Bill(2, "Bill_2", 15);
    Bill *bill3 = new Bill(3, "Bill_3", 99);
    Bill *bill4 = new Bill(4, "Bill_4", 44);
    Bill *bill5 = new Bill(5, "Bill_5", 150);
    std::cout << "=============== " << std::endl;
    // 全部先交给 level1 TeamLeader 审批
    level1->handleRequest(bill1);
    std::cout << "=============== " << std::endl;
    level1->handleRequest(bill2);
    std::cout << "=============== " << std::endl;
    level1->handleRequest(bill3);
    std::cout << "=============== " << std::endl;
    level1->handleRequest(bill4);
    std::cout << "=============== " << std::endl;
    level1->handleRequest(bill5);
    std::cout << "=============== " << std::endl;


    delete level1;delete level2;delete level3;delete level4;
    delete bill1;delete bill2;delete bill3;delete bill4;delete bill5;

    return 0;

}
