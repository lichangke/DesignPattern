#include "VisitorPattern.h"

int main() {

    Apple *apple1 = new Apple("红富士苹果", 7);
    Apple *apple2 = new Apple("烟台苹果", 5);
    Pork *pork1 = new Pork("里脊肉", 45);
    Pork *pork2 = new Pork("五花肉", 28);

    auto* cashier = new Cashier();
    auto* customer = new Customer("张三");
    customer->setNum(apple1, 3);
    customer->setNum(apple2, 4);
    customer->setNum(pork1, 1);
    customer->setNum(pork2, 2);

    auto* shoppingCart = new ShoppingCart();
    std::cout << "===购物车添加商品===" << std::endl;
    shoppingCart->addElement(apple1);
    shoppingCart->addElement(apple2);
    shoppingCart->addElement(pork1);
    shoppingCart->addElement(pork2);
    std::cout << "===顾客选择的商品===" << std::endl;
    shoppingCart->accept(customer);
    std::cout << "===收银员计算的价格===" << std::endl;
    shoppingCart->accept(cashier);
    std::cout << "========" << std::endl;

    delete apple1;delete apple2;
    delete pork1;delete pork2;
    delete cashier;delete customer;
    delete shoppingCart;
    return 0;
}
