#include "mystring.h"

#include <cstring>

int MyString::compare(const MyString& other) const {
    const std::size_t min_len = size_ < other.size_ ? size_ : other.size_;
    const char* lhs = data_ != nullptr ? data_ : "";
    const char* rhs = other.data_ != nullptr ? other.data_ : "";

    if (min_len > 0) {
        const int cmp = std::memcmp(lhs, rhs, min_len);
        if (cmp != 0) {
            return cmp < 0 ? -1 : 1;
        }
    }

    if (size_ < other.size_) {
        return -1;
    }
    if (size_ > other.size_) {
        return 1;
    }
    return 0;
}

bool MyString::operator==(const MyString& other) const {
    return compare(other) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return compare(other) != 0;
}

bool MyString::operator>(const MyString& other) const {
    return compare(other) > 0;
}

bool MyString::operator>=(const MyString& other) const {
    return compare(other) >= 0;
}

bool MyString::operator<(const MyString& other) const {
    return compare(other) < 0;
}

bool MyString::operator<=(const MyString& other) const {
    return compare(other) <= 0;
}
