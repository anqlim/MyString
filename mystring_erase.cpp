#include "mystring.h"

#include <cstring>

MyString& MyString::erase(int index, int count) {
    check_index_inclusive(index);
    if (count == 0) {
        return *this;
    }
    to_size(count);
    if (index + count > size_) {
        throw std::out_of_range("erase is out of range");
    }

    std::memmove(data_ + index, data_ + index + count, size_ - index - count);
    size_ -= count;
    data_[size_] = '\0';
    return *this;
}
