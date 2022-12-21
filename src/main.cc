#include "Bookstore.h"

#include <iostream>

#include "Utils/Exception.h"
#include "Utils/TokenScanner.h"

using bookstore::Bookstore;
using bookstore::input::BookstoreLexer;
using bookstore::input::BookstoreParser;

int output_status = 0;

void PrintHelp() {
    std::cout
        << "Bookstore 0.2 (Powered by Conless Pan, December 2022)\n"
        << "usage: (program name) [--show-status | -s] [--inherit-data | -i] "
           "[--help | -h] ...\n"
        << "Options and arguments (and corresponding environment variables:\n"
        << "\t--show-status, -s\t The option of printing the data.\n"
        << "\t\t0 (default)\t Running mode: only show standard output.\n"
        << "\t\t1\t\t Debugging mode: output the information of input.\n"
        << "\t\t2\t\t Showing mode: output all the data.\n"
        << "\t--inherit-data, -i\t The option of inheriting the data.\n"
        << "\t\t0\t\t Non-inheriting mode: do not inherit the recent data.\n"
        << "\t\t1 (default)\t Inheriting mode: inherit the recent data.\n"
        << "\t--help, -h\t\t Output helping information.\n";
}

void JudgeInput(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    for (int i = 1; i < argc; i++) {
        BookstoreLexer argv_div(argv[i], '=');
        bool err_flag = 0;
        if (argv_div[0] == "--help" || argv_div[0] == "-h") {
            PrintHelp();
            exit(0);
        } else if (argv_div[0] == "--show-status" || argv_div[0] == "-s") {
            if (argv_div.size() != 2)
                err_flag = 1;
            else if (argv_div[1] == "0")
                output_status = 0;
            else if (argv_div[1] == "1")
                output_status = 1;
            else if (argv_div[1] == "2")
                output_status = 2;
            else
                err_flag = 1;
        } else if (argv_div[0] == "--inherit-data" || argv_div[0] == "-i") {
            if (argv_div.size() != 2)
                err_flag = 1;
            else if (argv_div[1] == "0")
                std::filesystem::remove_all("data");
            else if (argv_div[1] == "1")
                ;
            else
                err_flag = 1;
        } else
            err_flag = 1;
        if (err_flag) {
            std::cerr << "Unexpected input parameters of " << argv_div[0]
                      << '\n';
            PrintHelp();
            exit(-1);
        }
    }
    return;
}

int main(int argc, char *argv[]) {
    JudgeInput(argc, argv);
    Bookstore root;
    std::string input;
    while (getline(std::cin, input)) {
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
                std::cout << ": " << msg.details();
            std::cout << '\n';
        } catch (const UnknownException &msg) {
            std::cout << "Invalid";
            if (output_status)
                std::cout << ": " << msg.details();
            std::cout << '\n';
        } catch (...) {
            std::cout << "?";
        }
        if (output_status == 2)
            root.output();
    }
    return 0;
}
