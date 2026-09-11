#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <cstddef>
#include <exception>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <string>
#include <utility>

class AhoCorasickAutomaton;

// mystring_6_1.cpp
class MyStringConversionError : public std::exception {
public:
    explicit MyStringConversionError(const char* message);
    const char* what() const noexcept override;

private:
    std::string message_;
};

class MyString {
public:
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    // mystring_constructors.cpp
    MyString();
    MyString(const char* source);
    MyString(const std::string& source);
    MyString(const MyString& other);
    MyString(const char* source, int count);
    MyString(const std::string& source, int count);
    MyString(const MyString& other, int count);
    MyString(int count, char ch);
    ~MyString();

    // mystring_6_1.cpp
    MyString(MyString&& other) noexcept;
    MyString(int value);
    MyString(double value);

    // mystring_core.cpp
    void clear();
    void shrink_to_fit();
    const char* c_str() const;
    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    // mystring_assignment.cpp
    MyString& operator=(const char* source);
    MyString& operator=(const std::string& source);
    MyString& operator=(const MyString& other);
    MyString& operator=(char ch);

    // mystring_accessors.cpp
    char& operator[](int index);
    const char& operator[](int index) const;
    char& operator[](iterator pos);
    const char& operator[](const_iterator pos) const;
    char& at(int index);
    const char& at(int index) const;
    char& at(iterator pos);
    const char& at(const_iterator pos) const;

    // mystring_append.cpp
    MyString& append(int count, char ch);
    MyString& append(const char* source);
    MyString& append(const std::string& source);
    MyString& append(const MyString& source);
    MyString& append(const char* source, int count);
    MyString& append(const std::string& source, int count);
    MyString& append(const MyString& source, int count);
    MyString& append(const char* source, int s_index, int count);
    MyString& append(const std::string& source, int s_index, int count);
    MyString& append(const MyString& source, int s_index, int count);

    // mystring_insert.cpp
    MyString& insert(int index, int count, char ch);
    MyString& insert(int index, const char* source);
    MyString& insert(int index, const std::string& source);
    MyString& insert(int index, const MyString& source);
    MyString& insert(int index, const char* source, int count);
    MyString& insert(int index, const std::string& source, int count);
    MyString& insert(int index, const MyString& source, int count);
    MyString& insert(int index, const char* source, int s_index, int count);
    MyString& insert(int index, const std::string& source, int s_index, int count);
    MyString& insert(int index, const MyString& source, int s_index, int count);
    MyString& insert(iterator pos, int count, char ch);
    MyString& insert(iterator pos, const char* source);
    MyString& insert(iterator pos, const std::string& source);
    MyString& insert(iterator pos, const MyString& source);
    MyString& insert(iterator pos, const char* source, int count);
    MyString& insert(iterator pos, const std::string& source, int count);
    MyString& insert(iterator pos, const MyString& source, int count);
    MyString& insert(iterator pos, const char* source, int s_index, int count);
    MyString& insert(iterator pos, const std::string& source, int s_index, int count);
    MyString& insert(iterator pos, const MyString& source, int s_index, int count);

    // mystring_erase.cpp
    MyString& erase(int index, int count);
    MyString& erase(iterator pos);
    MyString& erase(iterator first, iterator last);

    // mystring_replace.cpp
    MyString& replace(int index, int count, const char* source);
    MyString& replace(int index, int count, const std::string& source);
    MyString& replace(int index, int count, const MyString& source);
    MyString& replace(int index, int count, const char* source, int s_count);
    MyString& replace(int index, int count, const std::string& source, int s_count);
    MyString& replace(int index, int count, const MyString& source, int s_count);
    MyString& replace(int index, int count, const char* source, int s_index, int s_count);
    MyString& replace(int index, int count, const std::string& source, int s_index, int s_count);
    MyString& replace(int index, int count, const MyString& source, int s_index, int s_count);
    MyString& replace(iterator pos, int count, const char* source);
    MyString& replace(iterator pos, int count, const std::string& source);
    MyString& replace(iterator pos, int count, const MyString& source);
    MyString& replace(iterator pos, int count, const char* source, int s_count);
    MyString& replace(iterator pos, int count, const std::string& source, int s_count);
    MyString& replace(iterator pos, int count, const MyString& source, int s_count);
    MyString& replace(iterator pos, int count, const char* source, int s_index, int s_count);
    MyString& replace(iterator pos, int count, const std::string& source, int s_index, int s_count);
    MyString& replace(iterator pos, int count, const MyString& source, int s_index, int s_count);

    // mystring_substr.cpp
    MyString substr(int index) const;
    MyString substr(int index, int count) const;
    MyString substr(const_iterator pos) const;
    MyString substr(const_iterator pos, int count) const;
    MyString substr(const_iterator first, const_iterator last) const;

    // mystring_compare.cpp
    int compare(const MyString& other) const;
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator>(const MyString& other) const;
    bool operator>=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator<=(const MyString& other) const;

    // mystring_find.cpp
    int find(const char* pattern) const;
    int find(const char* pattern, int start) const;
    int find(const std::string& pattern) const;
    int find(const std::string& pattern, int start) const;
    int find(const MyString& pattern) const;
    int find(const MyString& pattern, int start) const;
    int find(const char* pattern, const_iterator start) const;
    int find(const std::string& pattern, const_iterator start) const;
    int find(const MyString& pattern, const_iterator start) const;

    // mystring_operators.cpp
    MyString& operator+=(const char* source);
    MyString& operator+=(const std::string& source);
    MyString& operator+=(const MyString& source);
    friend MyString operator+(const MyString& lhs, const char* rhs);
    friend MyString operator+(const MyString& lhs, const std::string& rhs);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);

    // mystring_6_1.cpp
    MyString& operator=(MyString&& other) noexcept;
    std::pair<int, int> find_any(std::initializer_list<const char*> patterns, int start = 0) const;
    std::pair<int, int> find_any(std::initializer_list<std::string> patterns, int start = 0) const;
    std::pair<int, int> find_any(std::initializer_list<MyString> patterns, int start = 0) const;
    int to_int() const;
    double to_float() const;
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);

    // mystring_iterators_6_2.cpp
    class iterator {
    public:
        using difference_type = std::ptrdiff_t;

        char& operator*();
        char* operator->();
        iterator& operator++();
        iterator operator++(int);

        friend bool operator==(const iterator& a, const iterator& b);
        friend bool operator!=(const iterator& a, const iterator& b);
        friend difference_type operator-(const iterator& a, const iterator& b);
        friend iterator operator+(const iterator& it, difference_type n);
        friend iterator operator+(difference_type n, const iterator& it);
        friend iterator operator-(const iterator& it, difference_type n);
        friend iterator& operator+=(iterator& it, difference_type n);
        friend iterator& operator-=(iterator& it, difference_type n);

    private:
        explicit iterator(char* ptr);
        char* ptr_;
        friend class MyString;
    };

    class const_iterator {
    public:
        using difference_type = std::ptrdiff_t;

        const char& operator*() const;
        const char* operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);

        friend bool operator==(const const_iterator& a, const const_iterator& b);
        friend bool operator!=(const const_iterator& a, const const_iterator& b);
        friend difference_type operator-(const const_iterator& a, const const_iterator& b);
        friend const_iterator operator+(const const_iterator& it, difference_type n);
        friend const_iterator operator+(difference_type n, const const_iterator& it);
        friend const_iterator operator-(const const_iterator& it, difference_type n);
        friend const_iterator& operator+=(const_iterator& it, difference_type n);
        friend const_iterator& operator-=(const_iterator& it, difference_type n);

    private:
        explicit const_iterator(const char* ptr);
        const char* ptr_;
        friend class MyString;
    };

    class reverse_iterator {
    public:
        using difference_type = std::ptrdiff_t;

        char& operator*();
        char* operator->();
        reverse_iterator& operator++();
        reverse_iterator operator++(int);

        friend bool operator==(const reverse_iterator& a, const reverse_iterator& b);
        friend bool operator!=(const reverse_iterator& a, const reverse_iterator& b);
        friend difference_type operator-(const reverse_iterator& a, const reverse_iterator& b);
        friend reverse_iterator operator+(const reverse_iterator& it, difference_type n);
        friend reverse_iterator operator+(difference_type n, const reverse_iterator& it);
        friend reverse_iterator operator-(const reverse_iterator& it, difference_type n);
        friend reverse_iterator& operator+=(reverse_iterator& it, difference_type n);
        friend reverse_iterator& operator-=(reverse_iterator& it, difference_type n);

    private:
        explicit reverse_iterator(char* ptr);
        char* ptr_;
        friend class MyString;
    };

    class const_reverse_iterator {
    public:
        using difference_type = std::ptrdiff_t;

        const char& operator*() const;
        const char* operator->() const;
        const_reverse_iterator& operator++();
        const_reverse_iterator operator++(int);

        friend bool operator==(const const_reverse_iterator& a, const const_reverse_iterator& b);
        friend bool operator!=(const const_reverse_iterator& a, const const_reverse_iterator& b);
        friend difference_type operator-(const const_reverse_iterator& a, const const_reverse_iterator& b);
        friend const_reverse_iterator operator+(const const_reverse_iterator& it, difference_type n);
        friend const_reverse_iterator operator+(difference_type n, const const_reverse_iterator& it);
        friend const_reverse_iterator operator-(const const_reverse_iterator& it, difference_type n);
        friend const_reverse_iterator& operator+=(const_reverse_iterator& it, difference_type n);
        friend const_reverse_iterator& operator-=(const_reverse_iterator& it, difference_type n);

    private:
        explicit const_reverse_iterator(const char* ptr);
        const char* ptr_;
        friend class MyString;
    };

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rcbegin() const;
    const_reverse_iterator rcend() const;

private:
    int index_from_iterator(iterator pos);
    int index_from_iterator(const_iterator pos) const;

    // mystring_core.cpp
    void init_from_cstr(const char* source, std::size_t count);
    void assign_from_cstr(const char* source, std::size_t count);
    void ensure_capacity(std::size_t min_capacity);
    static std::size_t to_size(int value);
    void check_index(int index) const;
    void check_index_inclusive(int index) const;

    // mystring_append.cpp
    void append_cstr(const char* source, std::size_t count);

    // mystring_insert.cpp
    void insert_cstr(int index, const char* source, std::size_t count);

    // mystring_replace.cpp
    void replace_impl(int index, std::size_t count, const char* source, std::size_t source_count);

    // mystring_find.cpp
    int find_impl(const char* pattern, std::size_t pattern_length, int start) const;

    // mystring_6_1.cpp
    std::pair<int, int> find_aho(AhoCorasickAutomaton& ac, int start) const;

    char* data_;
    std::size_t size_;
    std::size_t capacity_;
};

#endif // _MYSTRING_H_
