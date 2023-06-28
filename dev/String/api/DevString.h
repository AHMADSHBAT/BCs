#pragma once

#include "iostream"
#include "string"
#include <algorithm>
#include <unordered_set>
#include "vector"
#include <sstream>
namespace DEV {
void trim(std::string &s, char remove_char);


void trim(std::string &s, std::unordered_set<char> remove_chars);


void replace_all(std::string &input, const std::string &pattern, const std::string &replacement);


std::vector<std::string> tokenize(const std::string &input, char);

};
