#include <iostream>

#include "mystring.h"

static void demo(const char* title, const MyString& str) {
    std::cout << title << ": \"" << str.c_str() << "\""
              << " (size=" << str.size()
              << ", capacity=" << str.capacity() << ")\n";
}

int main() {
    std::cout << "MyString demo\n";
    std::cout << "full tests: ./build_test.sh\n\n";

    MyString str("Hello world!");
    demo("init", str);

    str.erase(5, 6);
    demo("erase(5, 6)", str);

    str.shrink_to_fit();
    demo("shrink_to_fit", str);

    MyString ins("aaaaa");
    ins.insert(0, 1, '!');
    ins.insert(3, 2, '@');
    demo("insert(0, 1, '!'); insert(3, 2, '@')", ins);

    MyString empty;
    demo("empty", empty);

    return 0;
}
