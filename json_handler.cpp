#include "json_handler.h"
#include <fstream>
#include <iostream>


bool JSONHandler::readFile(json& json_data) {
    std::ifstream input_file(file_name_);
    if (!input_file.is_open()) {
        std::cout << "The json file isn't open!" << std::endl;
        return false;
    }
    input_file >> json_data;
    if (json_data.is_null()) {
        std::cout << "The data from json is null!" << std::endl;
        return false;
    }
    input_file.close();
    return true;
}

bool JSONHandler::writeFile(json& json_data) {
    std::ofstream output_file(file_name_, std::ios::out);
    if (!output_file.is_open()) {
        std::cout << "The json file isn't open!" << std::endl;
        return false;
    }

    output_file << std::setw(4) << json_data;
    output_file.close();

    return true;
}

/*
bool JSONHandler::read_JSON(json& json_data) {
    // читаем данные из json файла
    if(readFile(json_data)) {
        std::cout << "The read data from json. " << std::endl;
        // std::cout << json_data.dump(4) << std::endl;
        return true;
    }
    return false;
}
*/