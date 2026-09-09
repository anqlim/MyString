#include "mystring.h"

MyString& MyString::operator+=(const char* source) {
    return append(source);
}

MyString& MyString::operator+=(const std::string& source) {
    return append(source);
}

MyString& MyString::operator+=(const MyString& source) {
    return append(source);
}

MyString operator+(const MyString& lhs, const char* rhs) {
    MyString result(lhs);
    result += rhs;
    return result;
}

MyString operator+(const MyString& lhs, const std::string& rhs) {
    MyString result(lhs);
    result += rhs;
    return result;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString result(lhs);
    result += rhs;
    return result;
}
