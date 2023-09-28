#include "trie.h"
#include <iostream>
#include <string>
#include <vector>

Trie::TrieNode::TrieNode() : isEndOfWord(false) {
    nodes_.resize(ALPHABET_SIZE);
    for(auto node : this->nodes_) {
        node = nullptr;
    }
}

Trie::Trie() { root_ = new TrieNode; }

Trie::~Trie() {
    if(root_ != nullptr) {
        delete_trie(root_);
    }
}

void Trie::delete_trie(TrieNode* node) {
    if(node == nullptr) {
        return;
    }
    for(auto curr_node : node->nodes_) {
        delete_trie(curr_node);
    }
    delete node;
}

void Trie::insert(const std::string& key) { insert(root_, key); }

void Trie::remove(const std::string& key) {
    if(root_ != nullptr) {
        root_ = remove(root_, key);
    }
}

bool Trie::search(const std::string& key) {
    if(root_ == nullptr) {
        return false;
    }
    return search(root_, key);
}

std::string Trie::get_word(const std::string& prefix) {
    if(root_ == nullptr) {
        return "";
    }
    std::string word{};
    if(get_word(root_, prefix, word)) {
        return word;
    } else {
        return ""; // Если слово не найдено
    }
}

void Trie::show_trie() {
    std::cout << "The trie is: \n";
    if(root_ != nullptr) {
        std::string prefix{};
        show_trie(root_, prefix);
    }
    std::cout << "\n";
}

void Trie::insert(TrieNode* node, std::string key) {
    if(key.empty()) {
        node->isEndOfWord = true;
        return;
    }
    int index = key[0] - 'a';
    if(node->nodes_[index] == nullptr) {
        node->nodes_[index] = new TrieNode();
    }
    insert(node->nodes_[index], key.substr(1));
}

Trie::TrieNode* Trie::remove(TrieNode* node, std::string key) {
    // если нет такого слова
    if(node == nullptr) {
        return node;
    }
    // если дошли до конца слова
    if(key.empty()) {
        if(node->isEndOfWord) {
            node->isEndOfWord = false;
        }
        // если дальше дерево пустое
        if(node->nodes_.empty()) {
            delete node;
            node = nullptr;
        }
        return node;

    } else { // если не дошли до конца слова
        int index = key[0] - 'a';
        node->nodes_[index] = remove(node->nodes_[index], key.substr(1));
    }
    // когда прошли все буквы в слове
    // если указатель не конец другого слова
    if(!node->isEndOfWord) {
        // если не имеет дочерних элементов или они раньше были удалены
        if(node->nodes_.empty()) {
            delete node;
            node = nullptr;
            return node;
        }
    }

    // присваиваем новый указатель
    return node;
}

void Trie::show_trie(const TrieNode* node, std::string& prefix) {
    if(node != nullptr && node->isEndOfWord == true) {
        std::cout << prefix << "\n";
    }
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(node->nodes_[i] != nullptr) {
            char ch = i + 'a';
            show_trie(node->nodes_[i], prefix + ch);
        }
    }
}

bool Trie::search(const TrieNode* node, std::string key) {
    if(key.empty()) {
        return node->isEndOfWord;
    } else {
        int index = key[0] - 'a';
        if(node->nodes_[index] == nullptr) {
            return false;
        }
        return search(node->nodes_[index], key.substr(1));
    }
}

bool Trie::get_word(TrieNode* node, const std::string prefix, std::string& word) {
    if(node == nullptr) {
        return false;
    }
    if(prefix.empty()) {
        while(node->count_children() > 0) {
            for(int i = 0; i < ALPHABET_SIZE; i++) {
                if(node->nodes_[i] != nullptr) {
                    word.push_back(i + 'a');
                    node = node->nodes_[i];
                    if(node->isEndOfWord) {
                        return true;
                    }
                    //break; // Переходим к следующей букве префикса
                }
            }
        }
        return false;
    } else {
        int index = prefix[0] - 'a';
        if(node->nodes_[index] == nullptr) {
            return false;
        }
        word.push_back(prefix[0]);
        return get_word(node->nodes_[index], prefix.substr(1), word);
    }
}

int Trie::TrieNode::count_children() {
    int counter = 0;
    if(this != nullptr) {
        for(int i = 0; i < ALPHABET_SIZE; i++) {
            if(this->nodes_[i] != nullptr) {
                counter++;
            }
        }
    }
    return counter;
}