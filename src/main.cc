#include "Bookstore.h"

#include <iostream>

#include "Utils/Exception.h"

using bookstore::Bookstore;
using bookstore::input::BookstoreLexer;
using bookstore::input::BookstoreParser;

void JudgeInput(int argc, char *argv[]) {
    // TODO
    return;
}

int main(int argc, char *argv[]) {
    JudgeInput(argc, argv);
    Bookstore master;
    while (true) {
        std::string input;
        getline(std::cin, input);
        try {
            BookstoreLexer token(input);
            BookstoreParser msg(token);
            master.AcceptMsg(msg);
        } catch (const Exception &err) {
            // TODO
            std::cout << err.msg << std::endl;
        }
    }
    return 0;
}