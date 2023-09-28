#pragma once
#include "nlohmann/json.hpp"
#include <string>

using json = nlohmann::json;

class JSONHandler {
  private:
    std::string file_name_;
  public:
    JSONHandler (std::string &file_name) : file_name_(file_name) {}
    bool readFile (json &json_data);
    bool writeFile (json &json_data);
    //bool read_JSON(nlohmann::json& json_data);
};