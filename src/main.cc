#include "Bookstore.h"

#include <iostream>

#include "Utils/Exception.h"
#include "Utils/TokenScanner.h"

using namespace bookstore;

int main(int argc, char *argv[]) {
    int output_status = JudgeInput(argc, argv);
    Bookstore root;
    std::string input;
    while (getline(std::cin, input)) {
        try {
            input::BookstoreLexer token(input);
            input::BookstoreParser msg(token);
            root.AcceptMsg(msg);
            if (output_status)
                std::cout << "Valid\n";
        } catch (const NormalException &msg) {
            if (msg.what() == QUIT_SYSTEM)
                break;
            if (msg.what() == EMPTY_INPUT)
                continue;
        } catch (const InputException &msg) {
            std::cout << "Invalid";
            if (output_status)
                std::cout << ": " << msg.details();
            std::cout << '\n';
        } catch (const InvalidException &msg) {
            std::cout << "Invalid";
            if (output_status)
                std::cout << ": " << msg.details();
            std::cout << '\n';
        } catch (...) {
            std::cout << "Program exited after throwing an unexpected error.\n";
            return -1;
        }
        if (output_status == 2)
            root.output();
    }
    return 0;
}
