#include "mystring.h"

#include <stdexcept>

MyString::iterator::iterator(char* ptr) : ptr_(ptr) {}

char& MyString::iterator::operator*() {
    return *ptr_;
}

char* MyString::iterator::operator->() {
    return ptr_;
}

MyString::iterator& MyString::iterator::operator++() {
    ++ptr_;
    return *this;
}

MyString::iterator MyString::iterator::operator++(int) {
    iterator temp = *this;
    ++ptr_;
    return temp;
}

bool operator==(const MyString::iterator& a, const MyString::iterator& b) {
    return a.ptr_ == b.ptr_;
}

bool operator!=(const MyString::iterator& a, const MyString::iterator& b) {
    return a.ptr_ != b.ptr_;
}

MyString::iterator::difference_type operator-(const MyString::iterator& a, const MyString::iterator& b) {
    return a.ptr_ - b.ptr_;
}

MyString::iterator operator+(const MyString::iterator& it, MyString::iterator::difference_type n) {
    return MyString::iterator(it.ptr_ + n);
}

MyString::iterator operator+(MyString::iterator::difference_type n, const MyString::iterator& it) {
    return MyString::iterator(it.ptr_ + n);
}

MyString::iterator operator-(const MyString::iterator& it, MyString::iterator::difference_type n) {
    return MyString::iterator(it.ptr_ - n);
}

MyString::iterator& operator+=(MyString::iterator& it, MyString::iterator::difference_type n) {
    it.ptr_ += n;
    return it;
}

MyString::iterator& operator-=(MyString::iterator& it, MyString::iterator::difference_type n) {
    it.ptr_ -= n;
    return it;
}

MyString::const_iterator::const_iterator(const char* ptr) : ptr_(ptr) {}

const char& MyString::const_iterator::operator*() const {
    return *ptr_;
}

const char* MyString::const_iterator::operator->() const {
    return ptr_;
}

MyString::const_iterator& MyString::const_iterator::operator++() {
    ++ptr_;
    return *this;
}

MyString::const_iterator MyString::const_iterator::operator++(int) {
    const_iterator temp = *this;
    ++ptr_;
    return temp;
}

bool operator==(const MyString::const_iterator& a, const MyString::const_iterator& b) {
    return a.ptr_ == b.ptr_;
}

bool operator!=(const MyString::const_iterator& a, const MyString::const_iterator& b) {
    return a.ptr_ != b.ptr_;
}

MyString::const_iterator::difference_type operator-(const MyString::const_iterator& a, const MyString::const_iterator& b) {
    return a.ptr_ - b.ptr_;
}

MyString::const_iterator operator+(const MyString::const_iterator& it,
                                     MyString::const_iterator::difference_type n) {
    return MyString::const_iterator(it.ptr_ + n);
}

MyString::const_iterator operator+(MyString::const_iterator::difference_type n,
                                     const MyString::const_iterator& it) {
    return MyString::const_iterator(it.ptr_ + n);
}

MyString::const_iterator operator-(const MyString::const_iterator& it,
                                     MyString::const_iterator::difference_type n) {
    return MyString::const_iterator(it.ptr_ - n);
}

MyString::const_iterator& operator+=(MyString::const_iterator& it, MyString::const_iterator::difference_type n) {
    it.ptr_ += n;
    return it;
}

MyString::const_iterator& operator-=(MyString::const_iterator& it, MyString::const_iterator::difference_type n) {
    it.ptr_ -= n;
    return it;
}

MyString::reverse_iterator::reverse_iterator(char* ptr) : ptr_(ptr) {}

char& MyString::reverse_iterator::operator*() {
    return *ptr_;
}

char* MyString::reverse_iterator::operator->() {
    return ptr_;
}

MyString::reverse_iterator& MyString::reverse_iterator::operator++() {
    --ptr_;
    return *this;
}

MyString::reverse_iterator MyString::reverse_iterator::operator++(int) {
    reverse_iterator temp = *this;
    --ptr_;
    return temp;
}

bool operator==(const MyString::reverse_iterator& a, const MyString::reverse_iterator& b) {
    return a.ptr_ == b.ptr_;
}

bool operator!=(const MyString::reverse_iterator& a, const MyString::reverse_iterator& b) {
    return a.ptr_ != b.ptr_;
}

MyString::reverse_iterator::difference_type operator-(const MyString::reverse_iterator& a,
                                                       const MyString::reverse_iterator& b) {
    return b.ptr_ - a.ptr_;
}

MyString::reverse_iterator operator+(const MyString::reverse_iterator& it,
                                       MyString::reverse_iterator::difference_type n) {
    return MyString::reverse_iterator(it.ptr_ - n);
}

MyString::reverse_iterator operator+(MyString::reverse_iterator::difference_type n,
                                       const MyString::reverse_iterator& it) {
    return MyString::reverse_iterator(it.ptr_ - n);
}

MyString::reverse_iterator operator-(const MyString::reverse_iterator& it,
                                       MyString::reverse_iterator::difference_type n) {
    return MyString::reverse_iterator(it.ptr_ + n);
}

MyString::reverse_iterator& operator+=(MyString::reverse_iterator& it,
                                         MyString::reverse_iterator::difference_type n) {
    it.ptr_ -= n;
    return it;
}

MyString::reverse_iterator& operator-=(MyString::reverse_iterator& it,
                                         MyString::reverse_iterator::difference_type n) {
    it.ptr_ += n;
    return it;
}

MyString::const_reverse_iterator::const_reverse_iterator(const char* ptr) : ptr_(ptr) {}

const char& MyString::const_reverse_iterator::operator*() const {
    return *ptr_;
}

const char* MyString::const_reverse_iterator::operator->() const {
    return ptr_;
}

MyString::const_reverse_iterator& MyString::const_reverse_iterator::operator++() {
    --ptr_;
    return *this;
}

MyString::const_reverse_iterator MyString::const_reverse_iterator::operator++(int) {
    const_reverse_iterator temp = *this;
    --ptr_;
    return temp;
}

bool operator==(const MyString::const_reverse_iterator& a, const MyString::const_reverse_iterator& b) {
    return a.ptr_ == b.ptr_;
}

bool operator!=(const MyString::const_reverse_iterator& a, const MyString::const_reverse_iterator& b) {
    return a.ptr_ != b.ptr_;
}

MyString::const_reverse_iterator::difference_type operator-(const MyString::const_reverse_iterator& a,
                                                            const MyString::const_reverse_iterator& b) {
    return b.ptr_ - a.ptr_;
}

MyString::const_reverse_iterator operator+(const MyString::const_reverse_iterator& it,
                                             MyString::const_reverse_iterator::difference_type n) {
    return MyString::const_reverse_iterator(it.ptr_ - n);
}

MyString::const_reverse_iterator operator+(MyString::const_reverse_iterator::difference_type n,
                                             const MyString::const_reverse_iterator& it) {
    return MyString::const_reverse_iterator(it.ptr_ - n);
}

MyString::const_reverse_iterator operator-(const MyString::const_reverse_iterator& it,
                                             MyString::const_reverse_iterator::difference_type n) {
    return MyString::const_reverse_iterator(it.ptr_ + n);
}

MyString::const_reverse_iterator& operator+=(MyString::const_reverse_iterator& it,
                                               MyString::const_reverse_iterator::difference_type n) {
    it.ptr_ -= n;
    return it;
}

MyString::const_reverse_iterator& operator-=(MyString::const_reverse_iterator& it,
                                               MyString::const_reverse_iterator::difference_type n) {
    it.ptr_ += n;
    return it;
}

MyString::iterator MyString::begin() {
    return iterator(data_);
}

MyString::iterator MyString::end() {
    return iterator(data_ != nullptr ? data_ + size_ : nullptr);
}

MyString::const_iterator MyString::cbegin() const {
    return const_iterator(data_);
}

MyString::const_iterator MyString::cend() const {
    return const_iterator(data_ != nullptr ? data_ + size_ : nullptr);
}

MyString::reverse_iterator MyString::rbegin() {
    if (size_ == 0) {
        return rend();
    }
    return reverse_iterator(data_ + size_ - 1);
}

MyString::reverse_iterator MyString::rend() {
    return reverse_iterator(data_ != nullptr ? data_ - 1 : nullptr);
}

MyString::const_reverse_iterator MyString::rcbegin() const {
    if (size_ == 0) {
        return rcend();
    }
    return const_reverse_iterator(data_ + size_ - 1);
}

MyString::const_reverse_iterator MyString::rcend() const {
    return const_reverse_iterator(data_ != nullptr ? data_ - 1 : nullptr);
}

int MyString::index_from_iterator(iterator pos) {
    if (data_ == nullptr) {
        if (pos.ptr_ != nullptr) {
            throw std::out_of_range("iterator is out of range");
        }
        return 0;
    }
    if (pos.ptr_ < data_ || pos.ptr_ > data_ + size_) {
        throw std::out_of_range("iterator is out of range");
    }
    return static_cast<int>(pos.ptr_ - data_);
}

int MyString::index_from_iterator(const_iterator pos) const {
    if (data_ == nullptr) {
        if (pos.ptr_ != nullptr) {
            throw std::out_of_range("iterator is out of range");
        }
        return 0;
    }
    if (pos.ptr_ < data_ || pos.ptr_ > data_ + size_) {
        throw std::out_of_range("iterator is out of range");
    }
    return static_cast<int>(pos.ptr_ - data_);
}

int MyString::index_from_iterator(reverse_iterator pos) {
    if ((data_ == nullptr && pos.ptr_ == nullptr) || (data_ != nullptr && pos.ptr_ == data_ - 1)) {
        return 0;
    }
    if (data_ == nullptr || pos.ptr_ < data_ || pos.ptr_ >= data_ + size_) {
        throw std::out_of_range("iterator is out of range");
    }
    return static_cast<int>(pos.ptr_ - data_);
}

int MyString::index_from_iterator(const_reverse_iterator pos) const {
    if ((data_ == nullptr && pos.ptr_ == nullptr) || (data_ != nullptr && pos.ptr_ == data_ - 1)) {
        return 0;
    }
    if (data_ == nullptr || pos.ptr_ < data_ || pos.ptr_ >= data_ + size_) {
        throw std::out_of_range("iterator is out of range");
    }
    return static_cast<int>(pos.ptr_ - data_);
}

char& MyString::operator[](iterator pos) {
    return (*this)[index_from_iterator(pos)];
}

const char& MyString::operator[](const_iterator pos) const {
    return (*this)[index_from_iterator(pos)];
}

char& MyString::at(iterator pos) {
    return at(index_from_iterator(pos));
}

const char& MyString::at(const_iterator pos) const {
    return at(index_from_iterator(pos));
}

MyString& MyString::insert(iterator pos, int count, char ch) {
    return insert(index_from_iterator(pos), count, ch);
}

MyString& MyString::insert(iterator pos, const char* source) {
    return insert(index_from_iterator(pos), source);
}

MyString& MyString::insert(iterator pos, const std::string& source) {
    return insert(index_from_iterator(pos), source);
}

MyString& MyString::insert(iterator pos, const MyString& source) {
    return insert(index_from_iterator(pos), source);
}

MyString& MyString::insert(iterator pos, const char* source, int count) {
    return insert(index_from_iterator(pos), source, count);
}

MyString& MyString::insert(iterator pos, const std::string& source, int count) {
    return insert(index_from_iterator(pos), source, count);
}

MyString& MyString::insert(iterator pos, const MyString& source, int count) {
    return insert(index_from_iterator(pos), source, count);
}

MyString& MyString::insert(iterator pos, const char* source, int s_index, int count) {
    return insert(index_from_iterator(pos), source, s_index, count);
}

MyString& MyString::insert(iterator pos, const std::string& source, int s_index, int count) {
    return insert(index_from_iterator(pos), source, s_index, count);
}

MyString& MyString::insert(iterator pos, const MyString& source, int s_index, int count) {
    return insert(index_from_iterator(pos), source, s_index, count);
}

MyString& MyString::erase(iterator pos) {
    return erase(index_from_iterator(pos), 1);
}

MyString& MyString::erase(iterator first, iterator last) {
    const int index = index_from_iterator(first);
    const int count = static_cast<int>(last - first);
    return erase(index, count);
}

MyString& MyString::replace(iterator pos, int count, const char* source) {
    return replace(index_from_iterator(pos), count, source);
}

MyString& MyString::replace(iterator pos, int count, const std::string& source) {
    return replace(index_from_iterator(pos), count, source);
}

MyString& MyString::replace(iterator pos, int count, const MyString& source) {
    return replace(index_from_iterator(pos), count, source);
}

MyString& MyString::replace(iterator pos, int count, const char* source, int s_count) {
    return replace(index_from_iterator(pos), count, source, s_count);
}

MyString& MyString::replace(iterator pos, int count, const std::string& source, int s_count) {
    return replace(index_from_iterator(pos), count, source, s_count);
}

MyString& MyString::replace(iterator pos, int count, const MyString& source, int s_count) {
    return replace(index_from_iterator(pos), count, source, s_count);
}

MyString& MyString::replace(iterator pos, int count, const char* source, int s_index, int s_count) {
    return replace(index_from_iterator(pos), count, source, s_index, s_count);
}

MyString& MyString::replace(iterator pos, int count, const std::string& source, int s_index, int s_count) {
    return replace(index_from_iterator(pos), count, source, s_index, s_count);
}

MyString& MyString::replace(iterator pos, int count, const MyString& source, int s_index, int s_count) {
    return replace(index_from_iterator(pos), count, source, s_index, s_count);
}

MyString MyString::substr(const_iterator pos) const {
    return substr(index_from_iterator(pos));
}

MyString MyString::substr(const_iterator pos, int count) const {
    return substr(index_from_iterator(pos), count);
}

MyString MyString::substr(const_iterator first, const_iterator last) const {
    return substr(index_from_iterator(first), static_cast<int>(last - first));
}

int MyString::find(const char* pattern, const_iterator start) const {
    return find(pattern, index_from_iterator(start));
}

int MyString::find(const std::string& pattern, const_iterator start) const {
    return find(pattern, index_from_iterator(start));
}

int MyString::find(const MyString& pattern, const_iterator start) const {
    return find(pattern, index_from_iterator(start));
}
