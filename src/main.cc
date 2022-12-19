#include "Bookstore.h"

#include <iostream>

#include "Utils/Exception.h"

using bookstore::Bookstore;
using bookstore::input::BookstoreLexer;
using bookstore::input::BookstoreParser;

int output_status = 0;

void JudgeInput(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--show-status=0"))
            output_status = 0;
        else if (!strcmp(argv[i], "--show-status=1"))
            output_status = 1;
        else if (!strcmp(argv[i], "--inherit-data=0"))
            std::filesystem::remove_all("data");
    }
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
        } catch (NormalException(QUIT_SYSTEM)) {
            break;
        } catch (const InvalidException &msg) {
            std::cout << "Invalid\n";
        } catch (...) {
            std::cout << "?\n";
        }
        if (output_status)
            master.output();
    }
    return 0;
}
