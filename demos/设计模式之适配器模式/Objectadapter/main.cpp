
#include "Adapter.h"
#include <list>

int main() {
    std::list<FilterTarget *> filterList;
    filterList.push_back(new FilterAdapter_A());
    filterList.push_back(new FilterAdapter_B());

    std::list<FilterTarget *>::iterator iter; //声明一个迭代器
    iter = filterList.begin();
    while (iter!=filterList.end()) {
        FilterTarget * filter = *iter++;
        filter->filter("this is a Adapter Design Pattern Demo");
    }

    while(!filterList.empty()) {
        FilterTarget * filter = filterList.front();
        filterList.pop_front();
        delete filter;
    }

    return 0;
}
