#include "mystring.h"

#include <cstring>
#include <stdexcept>

void MyString::clear() {
    size_ = 0;
    if (data_ != nullptr) {
        data_[0] = '\0';
    }
}

void MyString::shrink_to_fit() {
    if (size_ == 0) {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        return;
    }

    if (capacity_ == size_ + 1) {
        return;
    }

    char* new_data = new char[size_ + 1];
    std::memcpy(new_data, data_, size_);
    new_data[size_] = '\0';
    delete[] data_;
    data_ = new_data;
    capacity_ = size_ + 1;
}

const char* MyString::c_str() const {
    return data_ != nullptr ? data_ : "";
}

std::size_t MyString::size() const {
    return size_;
}

std::size_t MyString::capacity() const {
    return capacity_;
}

bool MyString::empty() const {
    return size_ == 0;
}

void MyString::assign_from_cstr(const char* source, std::size_t count) {
    if (count == 0) {
        clear();
        return;
    }

    if (data_ == nullptr || capacity_ < count + 1) {
        delete[] data_;
        data_ = new char[count + 1];
        capacity_ = count + 1;
    }

    std::memcpy(data_, source, count);
    data_[count] = '\0';
    size_ = count;
}

void MyString::init_from_cstr(const char* source, std::size_t count) {
    if (count == 0) {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        return;
    }

    data_ = new char[count + 1];
    std::memcpy(data_, source, count);
    data_[count] = '\0';
    size_ = count;
    capacity_ = count + 1;
}

std::size_t MyString::to_size(int value) {
    if (value < 0) {
        throw std::invalid_argument("count is negative");
    }
    return value;
}

void MyString::check_index(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("index is out of range");
    }
}

void MyString::check_index_inclusive(int index) const {
    if (index < 0 || index > size_) {
        throw std::out_of_range("index is out of range");
    }
}

void MyString::ensure_capacity(std::size_t min_capacity) {
    if (capacity_ >= min_capacity) {
        return;
    }

    char* new_data = new char[min_capacity];
    if (data_ != nullptr) {
        std::memcpy(new_data, data_, size_);
        delete[] data_;
    }
    new_data[size_] = '\0';
    data_ = new_data;
    capacity_ = min_capacity;
}
