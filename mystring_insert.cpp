#include "mystring.h"

#include <cstring>
#include <stdexcept>

void MyString::insert_cstr(int index, const char* source, std::size_t count) {
    check_index_inclusive(index);
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
    std::memmove(data_ + index + count, data_ + index, size_ - index);
    std::memcpy(data_ + index, insertion, count);
    size_ += count;
    data_[size_] = '\0';
}

MyString& MyString::insert(int index, int count, char ch) {
    check_index_inclusive(index);
    if (count == 0) {
        return *this;
    }
    to_size(count);

    ensure_capacity(size_ + count + 1);
    std::memmove(data_ + index + count, data_ + index, size_ - index);
    std::memset(data_ + index, ch, count);
    size_ += count;
    data_[size_] = '\0';
    return *this;
}

MyString& MyString::insert(int index, const char* source) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    insert_cstr(index, source, std::strlen(source));
    return *this;
}

MyString& MyString::insert(int index, const std::string& source) {
    insert_cstr(index, source.c_str(), source.size());
    return *this;
}

MyString& MyString::insert(int index, const MyString& source) {
    insert_cstr(index, source.data_, source.size_);
    return *this;
}

MyString& MyString::insert(int index, const char* source, int count) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    to_size(count);
    if (count > std::strlen(source)) {
        throw std::out_of_range("count exceeds source length");
    }
    insert_cstr(index, source, count);
    return *this;
}

MyString& MyString::insert(int index, const std::string& source, int count) {
    to_size(count);
    if (count > source.size()) {
        throw std::out_of_range("count exceeds source length");
    }
    insert_cstr(index, source.c_str(), count);
    return *this;
}

MyString& MyString::insert(int index, const MyString& source, int count) {
    to_size(count);
    if (count > source.size_) {
        throw std::out_of_range("count exceeds source length");
    }
    insert_cstr(index, source.data_, count);
    return *this;
}

MyString& MyString::insert(int index, const char* source, int s_index, int count) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    to_size(s_index);
    to_size(count);
    if (s_index > std::strlen(source) || count > std::strlen(source) - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    insert_cstr(index, source + s_index, count);
    return *this;
}

MyString& MyString::insert(int index, const std::string& source, int s_index, int count) {
    to_size(s_index);
    to_size(count);
    if (s_index > source.size() || count > source.size() - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    insert_cstr(index, source.c_str() + s_index, count);
    return *this;
}

MyString& MyString::insert(int index, const MyString& source, int s_index, int count) {
    to_size(s_index);
    to_size(count);
    if (s_index > source.size_ || count > source.size_ - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    insert_cstr(index, source.data_ + s_index, count);
    return *this;
}
