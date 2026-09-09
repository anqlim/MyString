#include "mystring_aho_corasick.h"

#include "mystring.h"

#include <cstring>
#include <limits>
#include <queue>

namespace {

void delete_subtree(AhoCorasickNode* node) {
    if (node == nullptr) {
        return;
    }
    for (auto& child : node->children) {
        delete_subtree(child.second);
    }
    delete node;
}

}

AhoCorasickNode::AhoCorasickNode()
    : is_terminal(false), pattern_id(-1), pattern_length(0), fail(nullptr) {}

AhoCorasickAutomaton::AhoCorasickAutomaton() {
    root_ = new AhoCorasickNode();
}

AhoCorasickAutomaton::~AhoCorasickAutomaton() {
    delete_subtree(root_);
}

void AhoCorasickAutomaton::add_pattern(const char* pattern, int pattern_id) {
    add_pattern_impl(pattern, strlen(pattern), pattern_id);
}

void AhoCorasickAutomaton::add_pattern(const std::string& pattern, int pattern_id) {
    add_pattern_impl(pattern.c_str(), pattern.length(), pattern_id);
}

void AhoCorasickAutomaton::add_pattern(const MyString& pattern, int pattern_id) {
    add_pattern_impl(pattern.c_str(), pattern.size(), pattern_id);
}

void AhoCorasickAutomaton::build() {
    root_->fail = root_;
    std::queue<AhoCorasickNode*> queue;

    for (auto& entry : root_->children) {
        entry.second->fail = root_;
        queue.push(entry.second);
    }

    while (!queue.empty()) {
        AhoCorasickNode* curr = queue.front();
        queue.pop();

        for (auto& entry : curr->children) {
            unsigned char ch = entry.first;
            AhoCorasickNode* child = entry.second;
            queue.push(child);

            AhoCorasickNode* f = curr->fail;
            while (f != root_ && f->children.find(ch) == f->children.end()) {
                f = f->fail;
            }
            auto it = f->children.find(ch);
            child->fail = (it != f->children.end()) ? it->second : root_;
        }
    }
}

std::pair<size_t, int> AhoCorasickAutomaton::find_first(const char* text,
                                                        std::size_t text_length,
                                                        std::size_t start) const {
    AhoCorasickNode* curr = root_;
    for (size_t i = start; i < text_length; ++i) {
        unsigned char ch = text[i];

        while (curr != root_ && curr->children.find(ch) == curr->children.end()) {
            curr = curr->fail;
        }
        auto it = curr->children.find(ch);
        if (it != curr->children.end()) {
            curr = it->second;
        }

        for (AhoCorasickNode* node = curr; node != root_; node = node->fail) {
            if (node->is_terminal) {
                return {i - node->pattern_length + 1, node->pattern_id};
            }
        }
    }
    return {std::numeric_limits<size_t>::max(), -1};
}

void AhoCorasickAutomaton::add_pattern_impl(const char* pattern, std::size_t length, int pattern_id) {
    AhoCorasickNode* curr = root_;
    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = pattern[i];
        if (curr->children.find(ch) == curr->children.end()) {
            curr->children[ch] = new AhoCorasickNode();
        }
        curr = curr->children[ch];
    }
    curr->is_terminal = true;
    curr->pattern_id = pattern_id;
    curr->pattern_length = length;
}
