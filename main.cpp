#include "client_code.h"
#include "json_handler.h"
#include "nlohmann/json.hpp"
#include "trie.h"
#include <iostream>
#include <string>

int main() {
    // создаем объект класса для работы с json файлом
    std::string file_name = "words.json";
    JSONHandler json_file(file_name);

    // создаем объект для работы с данными из json файла
    nlohmann::json json_data;
    // создаем объект префиксного дерева
    Trie* trie = nullptr;

    if (json_file.readFile(json_data)) {
        // загружаем словарь в префиксное дерево
        trie = load_dictionary_intoTrie (json_data);        
    }
    //trie->show_trie();

    //работаем со словарем
    clientCode (trie, json_file, json_data);

    //trie->show_trie();

    delete trie;
    return 0;
}