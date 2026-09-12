#include "mystring.h"

#include <cstring>
#include <stdexcept>

MyString& MyString::append(int count, char ch) {
    if (count == 0) {
        return *this;
    }
    to_size(count);

    ensure_capacity(size_ + count + 1);
    std::memset(data_ + size_, ch, count);
    size_ += count;
    data_[size_] = '\0';
    return *this;
}

MyString& MyString::append(const char* source) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    append_cstr(source, std::strlen(source));
    return *this;
}

MyString& MyString::append(const std::string& source) {
    append_cstr(source.c_str(), source.size());
    return *this;
}

MyString& MyString::append(const MyString& source) {
    append_cstr(source.data_, source.size_);
    return *this;
}

MyString& MyString::append(const char* source, int count) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    to_size(count);
    if (count > std::strlen(source)) {
        throw std::out_of_range("count exceeds source length");
    }
    append_cstr(source, count);
    return *this;
}

MyString& MyString::append(const std::string& source, int count) {
    to_size(count);
    if (count > source.size()) {
        throw std::out_of_range("count exceeds source length");
    }
    append_cstr(source.c_str(), count);
    return *this;
}

MyString& MyString::append(const MyString& source, int count) {
    to_size(count);
    if (count > source.size_) {
        throw std::out_of_range("count exceeds source length");
    }
    append_cstr(source.data_, count);
    return *this;
}

MyString& MyString::append(const char* source, int s_index, int count) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    to_size(s_index);
    to_size(count);
    if (s_index > std::strlen(source) || count > std::strlen(source) - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    append_cstr(source + s_index, count);
    return *this;
}

MyString& MyString::append(const std::string& source, int s_index, int count) {
    to_size(s_index);
    to_size(count);
    if (s_index > source.size() || count > source.size() - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    append_cstr(source.c_str() + s_index, count);
    return *this;
}

MyString& MyString::append(const MyString& source, int s_index, int count) {
    to_size(s_index);
    to_size(count);
    if (s_index > source.size_ || count > source.size_ - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    append_cstr(source.data_ + s_index, count);
    return *this;
}

void MyString::append_cstr(const char* source, std::size_t count) {
    if (count == 0) {
        return;
    }

    const char* insertion = source;
    MyString temp;
    if (data_ != nullptr && source != nullptr && source >= data_ && source < data_ + size_) {
        temp.init_from_cstr(source, count);
        insertion = temp.data_;
    }

    ensure_capacity(size_ + count + 1);
    std::memcpy(data_ + size_, insertion, count);
    size_ += count;
    data_[size_] = '\0';
}
