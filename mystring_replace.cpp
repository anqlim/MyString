#include "mystring.h"

#include <cstring>

namespace {

bool ranges_overlap(const char* first1, std::size_t len1, const char* first2, std::size_t len2) {
    return first1 < first2 + len2 && first2 < first1 + len1;
}

}

void MyString::replace_impl(int index, std::size_t count, const char* source, std::size_t source_count) {
    check_index_inclusive(index);
    if (count > size_ - index) {
        throw std::out_of_range("replace is out of range");
    }

    const char* replacement = source;
    std::size_t replacement_length = source_count;
    MyString temp;

    if (data_ != nullptr && source != nullptr &&
        ranges_overlap(data_ + index, count, source, source_count)) {
        temp.init_from_cstr(source, source_count);
        replacement = temp.data_;
        replacement_length = temp.size_;
    }

    if (replacement_length != count) {
        ensure_capacity(size_ - count + replacement_length + 1);
        std::memmove(data_ + index + replacement_length, data_ + index + count,
                     size_ - index - count);
    }

    if (replacement_length > 0) {
        std::memcpy(data_ + index, replacement, replacement_length);
    }

    size_ = size_ - count + replacement_length;
    if (data_ != nullptr) {
        data_[size_] = '\0';
    }
}

MyString& MyString::replace(int index, int count, const char* source) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    replace_impl(index, to_size(count), source, std::strlen(source));
    return *this;
}

MyString& MyString::replace(int index, int count, const std::string& source) {
    replace_impl(index, to_size(count), source.c_str(), source.size());
    return *this;
}

MyString& MyString::replace(int index, int count, const MyString& source) {
    replace_impl(index, to_size(count), source.data_, source.size_);
    return *this;
}

MyString& MyString::replace(int index, int count, const char* source, int s_count) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    to_size(s_count);
    if (s_count > std::strlen(source)) {
        throw std::out_of_range("count exceeds source length");
    }
    replace_impl(index, to_size(count), source, s_count);
    return *this;
}

MyString& MyString::replace(int index, int count, const std::string& source, int s_count) {
    to_size(s_count);
    if (s_count > source.size()) {
        throw std::out_of_range("count exceeds source length");
    }
    replace_impl(index, to_size(count), source.c_str(), s_count);
    return *this;
}

MyString& MyString::replace(int index, int count, const MyString& source, int s_count) {
    to_size(s_count);
    if (s_count > source.size_) {
        throw std::out_of_range("count exceeds source length");
    }
    replace_impl(index, to_size(count), source.data_, s_count);
    return *this;
}

MyString& MyString::replace(int index, int count, const char* source, int s_index, int s_count) {
    if (source == nullptr) {
        throw std::invalid_argument("source pointer is null");
    }
    to_size(s_index);
    to_size(s_count);
    if (s_index > std::strlen(source) || s_count > std::strlen(source) - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    replace_impl(index, to_size(count), source + s_index, s_count);
    return *this;
}

MyString& MyString::replace(int index, int count, const std::string& source, int s_index, int s_count) {
    to_size(s_index);
    to_size(s_count);
    if (s_index > source.size() || s_count > source.size() - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    replace_impl(index, to_size(count), source.c_str() + s_index, s_count);
    return *this;
}

MyString& MyString::replace(int index, int count, const MyString& source, int s_index, int s_count) {
    to_size(s_index);
    to_size(s_count);
    if (s_index > source.size_ || s_count > source.size_ - s_index) {
        throw std::out_of_range("substring is out of source range");
    }
    replace_impl(index, to_size(count), source.data_ + s_index, s_count);
    return *this;
}
