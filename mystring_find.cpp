#include "mystring.h"

#include <cstring>

int MyString::find_impl(const char* pattern, std::size_t pattern_length, int start) const {
    check_index_inclusive(start);
    if (pattern_length == 0) return start;
    if (start + pattern_length > size_) return -1;

    for (std::size_t i = start; i + pattern_length <= size_; ++i) {
        if (std::memcmp(data_ + i, pattern, pattern_length) == 0)
            return i;
    }
    return -1;
}

int MyString::find(const char* pattern) const {
    return find(pattern, 0);
}

int MyString::find(const char* pattern, int start) const {
    return find_impl(pattern, std::strlen(pattern), start);
}

int MyString::find(const std::string& pattern) const {
    return find(pattern, 0);
}

int MyString::find(const std::string& pattern, int start) const {
    return find_impl(pattern.c_str(), pattern.size(), start);
}

int MyString::find(const MyString& pattern) const {
    return find(pattern, 0);
}

int MyString::find(const MyString& pattern, int start) const {
    return find_impl(pattern.data_, pattern.size_, start);
}
