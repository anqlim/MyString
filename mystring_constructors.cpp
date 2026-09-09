#include "mystring.h"

#include <cstring>
#include <stdexcept>

MyString::MyString() : data_(nullptr), size_(0), capacity_(0) {}

MyString::MyString(const char* source) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    init_from_cstr(source, std::strlen(source));
}

MyString::MyString(const std::string& source) {
    init_from_cstr(source.c_str(), source.size());
}

MyString::MyString(const MyString& other) {
    init_from_cstr(other.data_, other.size_);
}

MyString::MyString(const char* source, int count) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    to_size(count);
    if (count > std::strlen(source)) {
        throw std::out_of_range("count exceeds source length");
    }
    init_from_cstr(source, count);
}

MyString::MyString(const std::string& source, int count) {
    to_size(count);
    if (count > source.size()) {
        throw std::out_of_range("count exceeds source length");
    }
    init_from_cstr(source.c_str(), count);
}

MyString::MyString(const MyString& other, int count) {
    to_size(count);
    if (count > other.size_) {
        throw std::out_of_range("count exceeds source length");
    }
    init_from_cstr(other.data_, count);
}

MyString::MyString(int count, char ch) {
    if (count == 0) {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        return;
    }
    to_size(count);

    data_ = new char[count + 1];
    std::memset(data_, ch, count);
    data_[count] = '\0';
    size_ = count;
    capacity_ = count + 1;
}

MyString::~MyString() {
    delete[] data_;
}
