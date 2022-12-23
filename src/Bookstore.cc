#include "Bookstore.h"

#include "User/UserSystem.h"
#include "Utils/Exception.h"

#include <cctype>
#include <string>
#include <utility>

namespace bookstore {

Bookstore::Bookstore() {
    // TODO
}
Bookstore::~Bookstore() {
    // TODO
}

bool validate(const std::string str) {
    for (const char &ch : str) {
        if (!(isalpha(ch) || isdigit(ch) || ch == '_'))
            return false;
    }
    return true;;
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
    if (str[0] == '.' || str[str.size() - 1] == '.')
        return std::make_pair(0.0, 0);
    for (const char &ch : str) {
        if (ch == '.') {
            if (dot_flag)
                return std::make_pair(0.0, 0);
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
        if (!validate(msg.args[0]) || !validate(msg.args[1]))
            throw InvalidException("?");
        if (msg.args[0].size() > 30 || msg.args[1].size() > 30)
            throw InvalidException("Check Length");
        UserSystem::UserLogin(msg.args[0].c_str(), msg.args[1].c_str());
        return;
    }
    if (msg.func == LOGOUT) {
        UserSystem::UserLogout();
        return;
    }
    if (msg.func == REG) {
        if (!validate(msg.args[0]) || !validate(msg.args[1]))
            throw InvalidException("?");
        if (msg.args[0].size() > 30 || msg.args[1].size() > 30)
            throw InvalidException("Check Length");
        UserSystem::UserRegister(msg.args[0].c_str(), msg.args[2].c_str(),
                                 msg.args[1].c_str());
        return;
    }
    if (msg.func == PASSWD) {
        if (!validate(msg.args[0]) || !validate(msg.args[1]) || !validate(msg.args[2]))
            throw InvalidException("?");
        if (msg.args[0].size() > 30 || msg.args[1].size() > 30 || msg.args[2].size() > 30)
            throw InvalidException("Check Length");
        UserSystem::ModifyPassword(msg.args[0].c_str(), msg.args[1].c_str(),
                                   msg.args[2].c_str());
        return;
    }
    if (msg.func == USERADD) {
        int priv;
        if (!validate(msg.args[0]) || !validate(msg.args[1]))
            throw InvalidException("?");
        if (msg.args[0].size() > 30 || msg.args[1].size() > 30)
            throw InvalidException("Check Length");
        if (msg.args[2] == "1")
            priv = 1;
        else if (msg.args[2] == "3")
            priv = 3;
        else if (msg.args[2] == "7")
            priv = 7;
        else
            throw InvalidException("Check privilege");
        UserSystem::UserAdd(msg.args[0].c_str(), msg.args[3].c_str(),
                            msg.args[1].c_str(), priv);
        return;
    }
    if (msg.func == DEL) {
        if (!validate(msg.args[0]))
            throw InvalidException("?");
        if (msg.args[0].size() > 30)
            throw InvalidException("Check Length");
        UserSystem::UserErase(msg.args[0].c_str());
        return;
    }
    if (msg.func == SHOW_ALL) {
        BookSystem::SearchAll();
        return;
    }
    if (msg.func == SHOW_ISBN) {
        if (!msg.args[0].size() || msg.args[0].size() > 20)
            throw InvalidException("Check Length");
        BookSystem::SearchByISBN(msg.args[0].c_str());
        return;
    }
    if (msg.func == SHOW_NAME) {
        if (!msg.args[0].size() || msg.args[0].size() > 60)
            throw InvalidException("Check Length");
        BookSystem::SearchByName(msg.args[0].c_str());
        return;
    }
    if (msg.func == SHOW_AUTHOR) {
        if (!msg.args[0].size() || msg.args[0].size() > 60)
            throw InvalidException("Check Length");
        BookSystem::SearchByAuthor(msg.args[0].c_str());
        return;
    }
    if (msg.func == SHOW_KEYWORD) {
        if (!msg.args[0].size() || msg.args[0].find('|') != std::string::npos)
            throw InvalidException("More than one keywords in show");
        BookSystem::SearchByKeyword(msg.args[0].c_str());
        return;
    }
    if (msg.func == BUY) {
        if (msg.args[0].size() > 20)
            throw InvalidException("Check Length");
        std::pair<int, bool> quan = str_to_int(msg.args[1]);
        if (!quan.first || !quan.second)
            throw InvalidException("Buy: Number error");
        BookSystem::BuyBook(msg.args[0].c_str(), quan.first);
        return;
    }
    if (msg.func == SEL) {
        if (msg.args[0].size() > 20)
            throw InvalidException("Check Length");
        int book_pos = BookSystem::SelectBook(msg.args[0].c_str());
        UserSystem::SelectBook(book_pos);
        return;
    }
    if (msg.func == MODIFY) {
        int book_pos = UserSystem::GetBook();
        if (UserSystem::GetBook() == 0)
            throw InvalidException("Modify a book before selecting it");
        if (msg.args[0].size() > 20 || msg.args[1].size() > 60 || msg.args[2].size() > 60 || msg.args[3].size() > 60 || msg.args[4].size() > 13)
            throw InvalidException("Check length");
        std::pair<double, bool> price = str_to_double(msg.args[4]);
        if (!price.second)
            throw InvalidException("Modify: Number error");
        if (msg.args[3][msg.args[3].size() - 1] == '|')
            throw InvalidException("?");
        BookstoreLexer key_div_str(msg.args[3], '|');
        std::set<std::string> key_div_set;
        std::vector<char *> key_div;
        key_div.resize(key_div_str.size());
        int siz = 0;
        for (std::string str : key_div_str) {
            if (!str.size())
                throw InvalidException("Check length");
            key_div[siz] = new char[65];
            strcpy(key_div[siz], str.c_str());
            siz++;
            if (!key_div_set.insert(str).second)
                throw InvalidException("Modify: duplicated keyword");
        }
        BookSystem::ModifyBook(book_pos, msg.args[0].c_str(),
                               msg.args[1].c_str(), msg.args[2].c_str(),
                               key_div, siz, price.first);
        return;
    }
    if (msg.func == IMPORT) {
        if (msg.args[0].size() > 10 || msg.args[1].size() > 13)
            throw InvalidException("Check length");
        std::pair<int, bool> quan = str_to_int(msg.args[0]);
        std::pair<double, bool> tot_cost = str_to_double(msg.args[1]);
        if (!quan.second || !tot_cost.second || !tot_cost.first)
            throw InvalidException("Import: Number error");
        BookSystem::ImportBook(UserSystem::GetBook(), quan.first,
                               tot_cost.first);
        return;
    }
    if (msg.func == FINANCE) {
        if (msg.args.size()) {
            std::pair<int, bool> rev = str_to_int(msg.args[0]);
            if (!rev.second)
                throw InvalidException("Finance: Number error");
            BookSystem::ShowFinance(rev.first);
        } else
            BookSystem::ShowFinance();
        return;
    }
    if (msg.func == LOG) {
        return;
    }
    throw InvalidException("Bookstore does NOT support this operation.");
}

void Bookstore::output() {
    UserSystem::output();
    BookSystem::output();
}

} // namespace bookstore

