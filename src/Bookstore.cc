#include "Bookstore.h"

#include "User/UserSystem.h"
#include "Utils/Exception.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <utility>

namespace bookstore {

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

int JudgeInput(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    int output_status = 0;
    for (int i = 1; i < argc; i++) {
        input::BookstoreLexer argv_div(argv[i], '=');
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
    return output_status;
}

Bookstore::Bookstore() {
    // TODO
}
Bookstore::~Bookstore() {
    // TODO
}

int to_authentity(const input::Function &func) {
    using namespace input;
    if (func == QUIT || func == SU || func == REG)
        return 0;
    if (func == LOGOUT || func == PASSWD || func == SHOW_ALL ||
        func == SHOW_ISBN || func == SHOW_NAME || func == SHOW_AUTHOR ||
        func == SHOW_KEYWORD || func == BUY)
        return 1;
    if (func == USERADD || func == SEL || func == MODIFY || func == IMPORT)
        return 3;
    return 7;
}

double str_to_double(const std::string str) {
    if (str == "-1")
        return -1.0;
    double tcost1 = 0, tcost2 = 0, tcost_div = 1.0;
    bool dot_flag = 0;
    for (const char &ch : str) {
        if (ch == '.')
            dot_flag = 1;
        else {
            if (!dot_flag)
                tcost1 = tcost1 * 10.0 + (double)(ch - '0');
            else {
                tcost2 = tcost2 * 10.0 + (double)(ch - '0');
                tcost_div *= 10.0;
            }
        }
    }
    if (dot_flag)
        tcost1 += tcost2 / tcost_div;
    return tcost1;
}

bool validate(const std::string &str) {
    for (const char &ch : str) {
        if (!(isalpha(ch) || isdigit(ch) || ch == '_'))
            return false;
    }
    return true;
}

void Bookstore::AcceptMsg(const input::BookstoreParser &msg) {
    using namespace input;
    if (UserSystem::GetIdentity() < to_authentity(msg.func))
        throw InvalidException("Check authority");
    if (msg.func == QUIT) {
        throw NormalException(QUIT_SYSTEM);
    } else if (msg.func == SU) {
        UserSystem::UserLogin(msg.args[0].c_str(), msg.args[1].c_str());
    } else if (msg.func == LOGOUT) {
        UserSystem::UserLogout();
    }
    if (msg.func == REG) {
        UserSystem::UserRegister(msg.args[0].c_str(), msg.args[2].c_str(),
                                 msg.args[1].c_str());
    }
    if (msg.func == PASSWD) {
        UserSystem::ModifyPassword(msg.args[0].c_str(), msg.args[1].c_str(),
                                   msg.args[2].c_str());
    } else if (msg.func == USERADD) {
        UserSystem::UserAdd(msg.args[0].c_str(), msg.args[3].c_str(),
                            msg.args[1].c_str(), std::stoi(msg.args[2]));
    } else if (msg.func == DEL) {
        UserSystem::UserErase(msg.args[0].c_str());
    }
    if (msg.func == FINANCE) {
        if (msg.args.size()) {
            BookSystem::ShowFinance(std::stoi(msg.args[0]));
        } else
            BookSystem::ShowFinance();
    } else if (msg.func == SHOW_ALL) {
        BookSystem::SearchAll();
    } else if (msg.func == SHOW_ISBN) {
        BookSystem::SearchByISBN(msg.args[0].c_str());
    } else if (msg.func == SHOW_NAME) {
        BookSystem::SearchByName(msg.args[0].c_str());
    } else if (msg.func == SHOW_AUTHOR) {
        BookSystem::SearchByAuthor(msg.args[0].c_str());
        return;
    } else if (msg.func == SHOW_KEYWORD) {
        if (msg.args[0].find('|') != std::string::npos)
            throw InvalidException("More than one keywords in show");
        BookSystem::SearchByKeyword(msg.args[0].c_str());
    } else if (msg.func == BUY) {
        BookSystem::BuyBook(msg.args[0].c_str(), std::stoi(msg.args[1]));
    } else if (msg.func == SEL) {
        int book_pos = BookSystem::SelectBook(msg.args[0].c_str());
        UserSystem::SelectBook(book_pos);
    } else if (msg.func == MODIFY) {
        int book_pos = UserSystem::GetBook();
        if (!book_pos)
            throw InvalidException("Modify a book before selecting it");
        if (msg.args[3][msg.args[3].size() - 1] == '|')
            throw InvalidException("Invalid keyword");
        BookstoreLexer key_div_str(msg.args[3], '|');
        std::vector<book::BookStr> key_div;
        key_div.resize(key_div_str.size());
        int siz = 0;
        for (std::string str : key_div_str) {
            if (!str.size())
                throw InvalidException("Check length");
            key_div[siz++] = str.c_str();
        }
        std::sort(key_div_str.begin(), key_div_str.end());
        for (int i = 1; i < siz; i++)
            if (key_div_str[i] == key_div_str[i - 1])
                throw InvalidException("Duplicated keyword");
        BookSystem::ModifyBook(book_pos, msg.args[0].c_str(),
                               msg.args[1].c_str(), msg.args[2].c_str(),
                               key_div, str_to_double(msg.args[4]));
    } else if (msg.func == IMPORT) {
        BookSystem::ImportBook(UserSystem::GetBook(), std::stoi(msg.args[0]),
                               str_to_double(msg.args[1]));
    } else if (msg.func == LOG) {
        system("cp data/Bookstore.log ./");
        system("vi -M Bookstore.log");
        return;
    }
    throw InvalidException("Bookstore does NOT support this operation.");
}

void Bookstore::output() {
    UserSystem::output();
    BookSystem::output();
}

} // namespace bookstore
