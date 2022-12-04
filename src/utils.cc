#include "utils.h"

#include <sstream>

std::vector<std::string> DivideMsg(const std::string &str_in_line) {
    std::stringstream ss(str_in_line);
    std::vector<std::string> words;
    std::string word;
    while (ss >> word)
        words.push_back(word);
    return words;
}
