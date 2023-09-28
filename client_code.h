#pragma once
#include "json_handler.h"
#include "nlohmann/json.hpp"
#include "trie.h"
#include <iostream>
#include <string>

Trie* load_dictionary_intoTrie(nlohmann::json& json_data) {
    Trie* trie = new Trie();
    for(std::string word : json_data["words"]) {
        trie->insert(word);
    }
    return trie;
}

bool val_input(const std::string& key) {
    bool alpha = true;
    // Перебираем каждый символ строки до тех пор, пока не дойдем до конца строки или до отклонения
    // символа
    for(unsigned int nIndex = 0; nIndex < key.length() && alpha; ++nIndex) {
        // Если текущий символ является буквой, то всё ок
        if(isalpha(key[nIndex]))
            continue;
        // Если пробел, то тоже ок
        if(key[nIndex] == ' ')
            continue;
        // В противном случае, отклоняем весь пользовательский ввод
        alpha = false;
    }
    return alpha;
}

int input_digit(const std::string& input) {
    int isDigitsOnly = 1;
    for(char ch : input) {
        if(!isdigit(ch)) {
            isDigitsOnly = 0;
            break;
        }
    }
    if(isDigitsOnly) {
        isDigitsOnly = std::stoi(input);
        if(isDigitsOnly < 1 && isDigitsOnly > 4) {
            std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
            isDigitsOnly = 0;
        }
    } else {
        std::cout << "Invalid input. Please enter a valid digit." << std::endl;
    }
    return isDigitsOnly;
}

// перегрузка оператора для выбора действия из консоли
enum class Action { Quit = 1, Find, Add, Remove };
std::istream& operator>>(std::istream& is, Action& act) {
    int tmp;
    if(is >> tmp) {
        act = static_cast<Action>(tmp);
    }
    return is;
}

void clientCode(Trie* trie, JSONHandler& json_file, nlohmann::json& json_data) {
    std::string text{};
    std::string curr_str{};
    std::string key{};
    std::string word{};

    while(true) {
        word.clear();
        key.clear();
        std::cout << "Text:\n" << text << std::endl;
        std::cout << "Type the word or any prefix, then ENTER: ";

        getline(std::cin, key);

        if(val_input(key)) {

            std::cout << "Select an action:" << std::endl;
            std::cout << "1 - quit, 2 - find a word in the dictionary by prefix,\n"
                         "3 - add to dictionary, 4 - remove from the dictionary: ";

            std::string input;
            std::cin >> input;
            int val = input_digit(input);

            if(val != 0) {
                Action action;
                action = static_cast<Action>(val);

                if(action == Action::Quit) {
                    break;
                }
                switch(action) {
                case Action::Find: {
                    word = trie->get_word(key);
                    if(word != "") {
                        std::cout << "Found word: " << word << "\n";
                        std::cout << "Add to the text (yes - \'y\' / no - any character): ";
                        std::string s;
                        // Очищаем символ новой строки из буфера
                        std::cin.ignore(32767, '\n');
                        std::getline(std::cin, s);
                        if(s == "y") {
                            text.append(word);
                            text.push_back('\n');
                        }
                    } else {
                        std::cin.ignore(32767, '\n');
                        std::cout << "A word by prefix \" " << key << " \" wasn't found. Try agan."
                                  << std::endl;
                    }
                    break;
                }
                case Action::Add: {
                    if(trie->search(key)) {
                        std::cout << "There is this word in the dictionary!" << std::endl;
                        std::cin.ignore(32767, '\n');
                        std::cout << "Try again!" << std::endl;
                    } else {
                        std::cout << "Add the word:\" " << key
                                  << "\" in the dictionary? (yes - \'y\' / no - any character): ";
                        std::string s;
                        // Очищаем символ новой строки из буфера
                        std::cin.ignore(32767, '\n');
                        std::getline(std::cin, s);
                        if(s == "y") {
                            // добавляем новое слово в префиксное дерево
                            trie->insert(key);
                            // добавляем новое слово в JSON файл
                            json_data["words"].push_back(key);
                            if(json_file.writeFile(json_data)) {
                                std::cout << "The word was written!" << std::endl;
                            }
                            text.append(key);
                            text.push_back('\n');
                        }
                    }
                    break;
                }
                case Action::Remove: {
                    std::cout << "Remove the word:\" " << key
                              << "\" from the dictionary? (yes - \'y\' / no - any character): ";
                    std::string s;
                    // Очищаем символ новой строки из буфера
                    std::cin.ignore(32767, '\n');
                    std::getline(std::cin, s);
                    if(s == "y") {
                        // удаляем слово из JSON файла
                        if(!json_data["words"].empty()) {
                            for(size_t i = 0; i < json_data["words"].size(); i++) {
                                if(json_data["words"][i] == key) {
                                    json_data["words"].erase(json_data["words"].begin() + i);
                                    break;
                                }
                            }
                            // сохраняем новые данные в файл
                            if(json_file.writeFile(json_data)) {
                                std::cout << "The data was written" << std::endl;
                            }
                        }
                        // читаем данные из json файла
                        if(json_file.readFile(json_data)) {
                            // загружаем словарь в префиксное дерево
                            trie = load_dictionary_intoTrie(json_data);
                        }
                    }
                    break;
                }
                default:
                    break;
                }
            } else {
                std::cin.ignore(32767, '\n');
                std::cout << "Try again!" << std::endl;
            }
        }
    }
}
