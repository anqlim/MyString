#include "mystring.h"

MyString MyString::substr(int index) const {
    check_index_inclusive(index);
    return substr(index, size_ - index);
}

MyString MyString::substr(int index, int count) const {
    check_index_inclusive(index);
    to_size(count);
    if (index + count > size_) {
        throw std::out_of_range("substring is out of range");
    }

    MyString result;
    result.init_from_cstr(data_ + index, count);
    return result;
}
