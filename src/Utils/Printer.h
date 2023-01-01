#ifndef BOOKSTORE_PRINTER_H
#define BOOKSTORE_PRINTER_H

#include <fstream>

enum Color {
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    PURPLE = 35,
    CYAN = 36,
    WHITE = 37
};

class Printer : public std::ofstream {
public:
    Printer(const std::string &_file_name) : std::ofstream(_file_name) {}
    void SetColor(Color col) { *this << "\033[" << col << "m"; }
    void Reset() { *this << "\033[0m"; }
};

#endif