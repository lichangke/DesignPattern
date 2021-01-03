
#include "ProxyPattern.h"

int main() {
    Subject *subject;
    subject = new ProxySubject();
    subject->business();
    delete subject;
    return 0;
}
