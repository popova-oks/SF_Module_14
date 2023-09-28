#pragma once
#include <iostream>
#include <string>
#include <vector>

const int ALPHABET_SIZE = 26;

class Trie {
    struct  TrieNode {
        std::vector <TrieNode*> nodes_;
        bool isEndOfWord;

        TrieNode ();
        ~TrieNode () = default;
        int count_children ();
    };
    
    private:
    TrieNode* root_;

  public:
    Trie();
    ~Trie();

    Trie (const Trie &) = delete;
    Trie& operator=(const Trie &) = delete;

    void insert(const std::string& key);
    bool search(const std::string& key);
    void remove(const std::string& key);
    std::string get_word (const std::string &prefix);
    void show_trie();

  private:
    void delete_trie(TrieNode* node);
    void insert(TrieNode *node, std::string key);
    TrieNode* remove(TrieNode *node, std::string key);
    void show_trie(const TrieNode* node, std::string &prefix);
    bool search(const TrieNode* node, std::string key);
    bool get_word (TrieNode* node, const std::string prefix, std::string &word);    
};