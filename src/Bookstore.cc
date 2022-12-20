#include "Bookstore.h"

#include "User/UserSystem.h"
#include "Utils/Exception.h"
#include <new>
#include <string>
#include <utility>

namespace bookstore {

Bookstore::Bookstore() {
    // TODO
}
Bookstore::~Bookstore() {
    // TODO
}

std::pair<int, bool> str_to_int(const std::string str) {
    int num = 0;
    for (const char &ch : str) {
        if (ch < '0' || ch > '9')
            return std::make_pair(0, 0);
        num = num * 10 + ch - '0';
    }
    return std::make_pair(num, 1);
}

std::pair<double, bool> str_to_double(const std::string str) {
    double tcost1 = 0, tcost2 = 0, tcost_div = 1.0;
    bool dot_flag = 0;
    for (const char &ch : str) {
        if (ch == '.' && !dot_flag) {
            dot_flag = 1;
            continue;
        }
        if (ch < '0' || ch > '9')
            return std::make_pair(0.0, 0);
        if (!dot_flag)
            tcost1 = tcost1 * 10.0 + (double)(ch - '0');
        else {
            tcost2 = tcost2 * 10.0 + (double)(ch - '0');
            tcost_div *= 10.0;
        }
    }
    if (dot_flag)
        tcost1 += tcost2 / tcost_div;
    return std::make_pair(tcost1, 1);
}

void Bookstore::AcceptMsg(const input::BookstoreParser &msg) {
    using namespace input;
    if (UserSystem::GetIdentity() < to_authentity(msg.func))
        throw InvalidException("Check authority");
    if (msg.func == QUIT)
        throw NormalException(QUIT_SYSTEM);
    if (msg.func == SU) {
        UserSystem::UserLogin(msg.args[0].c_str(), msg.args[1].c_str());
        return;
    }
    if (msg.func == LOGOUT) {
        UserSystem::UserLogout();
        return;
    }
    if (msg.func == REG) {
        UserSystem::UserRegister(msg.args[0].c_str(), msg.args[2].c_str(),
                                 msg.args[1].c_str());
        return;
    }
    if (msg.func == PASSWD) {
        UserSystem::ModifyPassword(msg.args[0].c_str(), msg.args[1].c_str(),
                                   msg.args[2].c_str());
        return;
    }
    if (msg.func == USERADD) {
        UserSystem::UserAdd(msg.args[0].c_str(), msg.args[3].c_str(),
                            msg.args[1].c_str(), std::stoi(msg.args[2]));
        return;
    }
    if (msg.func == DEL) {
        UserSystem::UserErase(msg.args[0].c_str());
        return;
    }
    if (msg.func == SHOW_ALL) {
        BookSystem::SearchAll();
        return;
    }
    if (msg.func == SHOW_ISBN) {
        BookSystem::SearchByISBN(msg.args[0].c_str());
        return;
    }
    if (msg.func == SHOW_NAME) {
        BookSystem::SearchByName(msg.args[0].c_str());
        return;
    }
    if (msg.func == SHOW_AUTHOR) {
        BookSystem::SearchByAuthor(msg.args[0].c_str());
        return;
    }
    if (msg.func == SHOW_KEYWORD) {
        if (msg.args[0].find('|') != std::string::npos)
            throw InvalidException("More than one keywords in show");
        BookSystem::SearchByKeyword(msg.args[0].c_str());
        return;
    }
    if (msg.func == BUY) {
        std::pair<int, bool> quan = str_to_int(msg.args[0]);
        if (!quan.second)
            throw InvalidException("Buy: Number error");
        BookSystem::BuyBook(msg.args[0].c_str(), quan.first);
        return;
    }
    if (msg.func == SEL) {
        UserSystem::SelectBook(msg.args[0].c_str());
        BookSystem::SelectBook(msg.args[0].c_str());
        return;
    }
    if (msg.func == MODIFY) {
        std::string selected_book = UserSystem::GetBook();
        if (UserSystem::GetBook() == "")
            throw InvalidException("Modify a book before selecting it");
        std::pair<double, bool> price = str_to_double(msg.args[4]);
        if (!price.second)
            throw InvalidException("Modify: Number error");
        BookSystem::ModifyBook(selected_book.c_str(), msg.args[0].c_str(),
                               msg.args[1].c_str(), msg.args[2].c_str(),
                               msg.args[3].c_str(), price.first);
        if (msg.args[0] != "")
            UserSystem::SelectBook(msg.args[0].c_str());
        return;
    }
    if (msg.func == IMPORT) {
        std::pair<int, bool> quan = str_to_int(msg.args[0]);
        std::pair<double, bool> tot_cost = str_to_double(msg.args[1]);
        if (!quan.second || !tot_cost.second)
            throw InvalidException("Import: Number error");
        BookSystem::ImportBook(UserSystem::GetBook().c_str(), quan.first,
                               tot_cost.first);
        return;
    }
    throw InvalidException("Bookstore does NOT support this operation.");
}

void Bookstore::output() {
    UserSystem::output();
    BookSystem::output();
}

} // namespace bookstore