#include "mystring.h"

char& MyString::operator[](int index) {
    check_index(index);
    return data_[index];
}

const char& MyString::operator[](int index) const {
    check_index(index);
    return data_[index];
}

char& MyString::at(int index) {
    check_index(index);
    return data_[index];
}

const char& MyString::at(int index) const {
    check_index(index);
    return data_[index];
}
