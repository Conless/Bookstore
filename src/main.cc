#include "Bookstore.h"

#include <iostream>

#include "Utils/Exception.h"

using bookstore::Bookstore;
using bookstore::input::BookstoreLexer;
using bookstore::input::BookstoreParser;

int output_status = 0;

void JudgeInput(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--show-status=0"))
            output_status = 0;
        else if (!strcmp(argv[i], "--show-status=1"))
            output_status = 1;
        else if (!strcmp(argv[i], "--show-status=2"))
            output_status = 2;
        else if (!strcmp(argv[i], "--inherit-data=0"))
            std::filesystem::remove_all("data");
    }
    return;
}

int main(int argc, char *argv[]) {
    JudgeInput(argc, argv);
    Bookstore root;
        std::string input;
    while (
        getline(std::cin, input)) {
        try {
            BookstoreLexer token(input);
            BookstoreParser msg(token);
            root.AcceptMsg(msg);
            if (output_status)
                std::cout << "Valid\n";
        } catch (NormalException(QUIT_SYSTEM)) {
            break;
        } catch (const InvalidException &msg) {
            std::cout << "Invalid";
            if (output_status)
                std::cout << ": " << msg.what();
            std::cout << '\n';
        } catch (const UnknownException &msg) {
            std::cout << "Invalid";
            if (output_status)
                std::cout << ": " << msg.what();
            std::cout << '\n';
        } catch (...) {
            std::cout << "?";
        }
        if (output_status == 2)
            root.output();
    }
    return 0;
}
