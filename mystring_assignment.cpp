#include "mystring.h"

#include <cstring>
#include <stdexcept>

MyString& MyString::operator=(const char* source) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    assign_from_cstr(source, std::strlen(source));
    return *this;
}

MyString& MyString::operator=(const std::string& source) {
    assign_from_cstr(source.c_str(), source.size());
    return *this;
}

MyString& MyString::operator=(const MyString& other) {
    if (this == &other) {
        return *this;
    }
    assign_from_cstr(other.data_, other.size_);
    return *this;
}

MyString& MyString::operator=(char ch) {
    assign_from_cstr(&ch, 1);
    return *this;
}
