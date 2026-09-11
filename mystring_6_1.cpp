#include "mystring.h"

#include "mystring_aho_corasick.h"

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>

MyStringConversionError::MyStringConversionError(const char* message)
    : message_(message) {}

const char* MyStringConversionError::what() const noexcept {
    return message_.c_str();
}

MyString::MyString(MyString&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
}

MyString::MyString(int value) {
    if (value == 0) {
        init_from_cstr("0", 1);
        return;
    }

    char buffer[12];
    std::size_t pos = 0;
    long long n = value;

    if (n < 0) {
        buffer[pos++] = '-';
        n = -n;
    }

    char digits[11];
    std::size_t digit_count = 0;
    while (n > 0) {
        digits[digit_count++] = '0' + (n % 10);
        n /= 10;
    }

    while (digit_count > 0) {
        buffer[pos++] = digits[--digit_count];
    }

    init_from_cstr(buffer, pos);
}

MyString::MyString(double value) {
    if (std::isnan(value) || std::isinf(value)) {
        throw MyStringConversionError("cannot convert non-finite double to string");
    }

    char buffer[64];
    const int length = std::snprintf(buffer, sizeof(buffer), "%g", value);
    init_from_cstr(buffer, length);
}

int MyString::to_int() const {
    if (empty()) {
        throw MyStringConversionError("cannot convert empty string to int");
    }

    const char* p = c_str();
    bool negative = false;

    if (*p == '-') {
        negative = true;
        ++p;
    }
    else if (*p == '+') {
        ++p;
    }

    if (*p == '\0') {
        throw MyStringConversionError("invalid integer format");
    }

    long long result = 0;
    while (*p != '\0') {
        if (*p < '0' || *p > '9') {
            throw MyStringConversionError("invalid integer format");
        }
        result = result * 10 + (*p - '0');
        ++p;
    }

    return negative ? -result : result;
}

double MyString::to_float() const {
    if (empty()) {
        throw MyStringConversionError("cannot convert empty string to double");
    }

    char* end = nullptr;
    const double value = std::strtod(c_str(), &end);
    if (end == c_str() || *end != '\0') {
        throw MyStringConversionError("invalid double format");
    }
    if (std::isnan(value) || std::isinf(value)) {
        throw MyStringConversionError("cannot convert non-finite double");
    }

    return value;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os.write(str.c_str(), str.size());
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    str.clear();

    int ch = is.get();
    while (ch != EOF && std::isspace(ch)) {
        ch = is.get();
    }

    if (ch == EOF) {
        is.setstate(std::ios::failbit);
        return is;
    }

    char c = ch;
    str.append(1, c);
    ch = is.get();
    while (ch != EOF && !std::isspace(ch)) {
        c = ch;
        str.append(1, c);
        ch = is.get();
    }

    if (ch != EOF) {
        is.unget();
    }
    return is;
}

std::pair<int, int> MyString::find_aho(AhoCorasickAutomaton& ac, int start) const {
    ac.build();
    auto result = ac.find_first(c_str(), size_, start);
    if (result.second == -1) {
        return {-1, -1};
    }
    return {result.first, result.second};
}

std::pair<int, int> MyString::find_any(std::initializer_list<const char*> patterns, int start) const {
    check_index_inclusive(start);
    AhoCorasickAutomaton ac;
    int id = 0;
    for (const char* pattern : patterns) {
        ac.add_pattern(pattern, id);
        ++id;
    }
    return find_aho(ac, start);
}

std::pair<int, int> MyString::find_any(std::initializer_list<std::string> patterns, int start) const {
    check_index_inclusive(start);
    AhoCorasickAutomaton ac;
    int id = 0;
    for (const std::string& pattern : patterns) {
        ac.add_pattern(pattern, id);
        ++id;
    }
    return find_aho(ac, start);
}

std::pair<int, int> MyString::find_any(std::initializer_list<MyString> patterns, int start) const {
    check_index_inclusive(start);
    AhoCorasickAutomaton ac;
    int id = 0;
    for (const MyString& pattern : patterns) {
        ac.add_pattern(pattern, id);
        ++id;
    }
    return find_aho(ac, start);
}
