#ifndef _MYSTRING_AHO_CORASICK_H_
#define _MYSTRING_AHO_CORASICK_H_

#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>

class MyString;

struct AhoCorasickNode {
    AhoCorasickNode();
    bool is_terminal;
    int pattern_id;
    size_t pattern_length;
    std::unordered_map<unsigned char, AhoCorasickNode*> children;
    AhoCorasickNode* fail;
};

class AhoCorasickAutomaton {
public:
    AhoCorasickAutomaton();
    ~AhoCorasickAutomaton();

    void add_pattern(const char* pattern, int pattern_id);
    void add_pattern(const std::string& pattern, int pattern_id);
    void add_pattern(const MyString& pattern, int pattern_id);

    void build();

    std::pair<size_t, int> find_first(const char* text, std::size_t text_length, std::size_t start) const;

private:
    AhoCorasickNode* root_;
    void add_pattern_impl(const char* pattern, std::size_t length, int pattern_id);
};

#endif // _MYSTRING_AHO_CORASICK_H_
