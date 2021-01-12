#include "VisitorPattern.h"

int main() {

    Apple *apple1 = new Apple("红富士苹果", 7);
    Apple *apple2 = new Apple("花牛苹果", 5);
    Pork *book1 = new Pork("红楼梦", 129);
    Pork *book2 = new Pork("终结者", 49);

    auto* cashier = new Cashier();
    auto* jungle = new Customer("Jungle");
    jungle->setNum(apple1, 2);
    jungle->setNum(apple2, 4);
    jungle->setNum(book1, 1);
    jungle->setNum(book2, 3);

    auto* shoppingCart = new ShoppingCart();
    shoppingCart->addElement(apple1);
    shoppingCart->addElement(apple2);
    shoppingCart->addElement(book1);
    shoppingCart->addElement(book2);

    shoppingCart->accept(jungle);

    shoppingCart->accept(cashier);



    return 0;
}
