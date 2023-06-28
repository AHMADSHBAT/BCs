#pragma once
#include "iostream"
#include "string"
#include <algorithm>
#include <unordered_set>
#include "vector"
#include "../api/DevString.h"

namespace DEV {
void trim(std::string &s, std::unordered_set<char> remove_chars)
{
    s.erase(std::remove_if(s.begin(), s.end(), [&](char ch) {
        return remove_chars.count(ch) > 0;
    }), s.end());
}

void replace_all(std::string &input, const std::string &pattern, const std::string &replacement)
{
    size_t start_pos = 0;
    // std::string::npos is a constant static member of the std::string, It represents the maximum value for the size_t type and is used 
    // to indicate the absence or failure of a specific position or substring within a string.
    while ((start_pos = input.find(pattern, start_pos)) != std::string::npos)
    {
        input.replace(start_pos, pattern.length(), replacement);
        start_pos += replacement.length();
    }
}





std::vector<std::string> tokenize(const std::string &input, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    //the getline func will store all the chars from the ss stream into the token buffer
    //until we hit the delimiter or the end of the line if no occurence was hit.
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
};