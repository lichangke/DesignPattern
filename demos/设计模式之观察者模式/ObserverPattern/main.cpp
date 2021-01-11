#include "ObserverPattern.h"

int main() {
    Blog *blog = new BlogCSDN("墨1024");
    Observer *observer1 = new ObserverBlog("张三",blog);
    Observer *observer2 = new ObserverBlog("李四",blog);

    blog->attach(observer1);
    blog->attach(observer2);


    std::cout << "==================" << std::endl;
    blog->setStatus("发表了一篇Blog");
    blog->notify();
    std::cout << "==================" << std::endl;
    blog->remove(observer1);
    blog->setStatus("更新了一条blink");
    blog->notify();
    std::cout << "==================" << std::endl;
    delete blog;
    delete observer1;
    delete observer2;
    return 0;
}
