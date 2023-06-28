#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include "dev/String/api/DevString.h"

using namespace DEV;
int main()
{
    // Demonstrate the functions from DevString.cpp
    std::string str = "   !Hello!!!!!!!!Wor!ld!   ";
    std::cout << "to be trimmed: " << str << std::endl;
    std::unordered_set<char> removeChars = {' ', '!'};
    trim(str, removeChars);
    std::cout << "Trimmed string: " << str << std::endl;

    std::string input = "Hello, Hello, Hello";
    std::string pattern = "Hello";
    std::string replacement = "Hi";
    std::cout << "replacing Hello with Hi of '" << input << "'" << std::endl;
    replace_all(input, pattern, replacement);
    std::cout << "Replaced string: " << input << std::endl;

    std::string tokens = "Hello,World,AHMAD,SHBAT";
    std::cout << "\nTokenizing: " <<  tokens << std::endl;
    char delimiter = ',';
    std::vector<std::string> tokenizedStrings = tokenize(tokens, delimiter);
    std::cout <<"\nTokenized strings: " << std::endl;
    for (const std::string& token : tokenizedStrings)
    {
        std::cout << token << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
